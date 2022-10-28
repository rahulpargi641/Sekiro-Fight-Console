#include "Sekiro.h"

std::vector <std::future<void>> PoisonThread;

Sekiro::Sekiro()
{
    m_Name = "Sekiro";
    m_Health = m_MaxHealth;
    m_VitalityGain = 100;
    m_BaseDamage = 30;
    m_ConsumableItems = 3; // Genshin's sugar

    bSpiritEmblems = false;
    bDrawMortalBlade = false;
    m_HealingGourds = 5;
    m_MortalSwordDamage = m_BaseDamage * 6;
}

void Sekiro::TurnStats(Player* Enemy) const
{
    std::cout << "Sekiro's Turn!    ";
    std::cout << "Sekiro's Health: " << m_Health << "    ||    Enemy's Health: " << Enemy->GetHealth() <<"    ||    Healing Gourds: " << m_HealingGourds 
        << "    ||    Consumables: " << m_ConsumableItems << std::endl;
}

void Sekiro::Attack1(Player* Enemy)
{
    DealDamage(Enemy);
    std::cout << "Sekiro Attacked!, Floating Passage!,  ";
    std::cout << "Damage Done: " << m_BaseDamage << std::endl;
    std::cout << "" << std::endl;
}

void Sekiro::Attack2(Player* Enemy)
{
    std::cout << "Sekiro Attacked! Piercing Sabimaru!" << std::endl;
    std::cout << Enemy->m_Name << " infected with poison, ";
    std::cout << Enemy->m_Name << " vitality slowly degenrating..." << std::endl;
    std::cout << "" << std::endl;
    PoisonThread.push_back(std::async(std::launch::async, InflictPoisonEffect, Enemy));
}

void Sekiro::Heal()
{
    if (m_Health == m_MaxHealth)
    {
        std::cout << "Vitality is Full !" << std::endl;
        std::cout << "" << std::endl;
    }
    else if (m_HealingGourds > 0 && m_Health < m_MaxHealth)
    {
        m_Health += m_VitalityGain;
        if (m_Health > m_MaxHealth) m_Health = m_MaxHealth;
        m_HealingGourds--;
        std::cout << "Sekiro Used Healing Gourd to Heal !" << std::endl;
        std::cout << "Sekiro's Health is now: " << m_Health << std::endl;
        std::cout << "" << std::endl;
    }
    else
    {
        std::cout << "Healing Gourd Empty !" << std::endl; // meed to fix two times in a row healing by 2d array
        std::cout << "" << std::endl;
    }

}

void Sekiro::PerformRitual()
{
    if (m_Health >= (m_MaxHealth / 2))
    {
        m_Health = m_Health - (m_Health / 4);
        bSpiritEmblems = true;
        std::cout << "Sekiro Perfomed Ritual!, Spirit emblems gained! " << std::endl;
        std::cout << "Mortal Sword can be used, Attack power 500% !" << std::endl;
        std::cout << "Press 'Z' to use to Attack with the Mortal Sword!, Sekiro's Turn Again!" << std::endl;
        std::cout << "" << std::endl;
    }
    else
    {
        std::cout << "Not enough Vitality to perform Ritual!, Sekiro's turn again" << std::endl;
        std::cout << "" << std::endl;
    }
}

void Sekiro::DrawMortalBlade(Player* Enemy)
{
    std::cout << "Sekiro used Mortal sword to Attack,  Damage Done: " << m_MortalSwordDamage << std::endl;
    std::cout << "" << std::endl;
    int EnemyHealth = Enemy->GetHealth();
    EnemyHealth -= m_MortalSwordDamage;
    Enemy->SetHealth(EnemyHealth);

    bSpiritEmblems = false;
}

void Sekiro::ActivateSpecialAbility(Player* Enemy, bool& bKeepTurn) 
{
    if (bSpiritEmblems)
    {
        DrawMortalBlade(Enemy);
    }
    else
    {
        PerformRitual();
        bKeepTurn = true;
    }
}


void Sekiro::InflictPoisonEffect(Player* Enemy)
{
    using namespace std::literals::chrono_literals;

    int EnemyHealth = Enemy->GetHealth();
        for (int i = 0; i < m_DegenerateDuration; i++)
        {
            std::this_thread::sleep_for(1s);
            if (!EnemyHealth <= 0)
            {
                EnemyHealth -= m_Degenerate;
                Enemy->SetHealth(EnemyHealth);
            }
            else
                break;
        }
        if (!EnemyHealth <= 0)
        {
            std::cout << "--------------------------------" << std::endl;
            std::cout << "Poison Effect wore off, "<< Enemy->m_Name <<"'s Vitality is now: " << EnemyHealth << std::endl;
            std::cout << "" << std::endl;
        }
        else
            std::cout << Enemy->m_Name << "'s Vitality is Zero Due to the Posioning Effect!" << std::endl;
}