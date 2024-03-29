#include "Sekiro.h"

using namespace std::literals::chrono_literals;

static int s_DegenerateDamage = 3;
static int s_DegenerateDuration = 15;

Sekiro::Sekiro()
{
    m_Name = "Sekiro";
    m_CurrentHealth = Max_Health;
    m_VitalityGain = 100;
    m_BaseDamage = 30;
    m_AdditionalDamage = 15;
    m_ConsumableItems = 3; // Genshin's sugar

    m_HasSpiritEmblems = false;
    m_CanDrawMortalBlade = false;
    m_HealingGourds = 5;
    m_RitualVitalityReduction = 4;
    m_MortalSwordDamage = m_BaseDamage * 6; // 500% more attack power
}

void Sekiro::DisplayPlayerStats(Player* opponentPlayer) const
{
    std::cout << "Sekiro's Turn!    ";
    std::cout << "Sekiro's Health: " << m_CurrentHealth << "    ||    Enemy's Health: " << opponentPlayer->GetHealth() <<"    ||    Healing Gourds: " << m_HealingGourds 
        << "    ||    Consumables: " << m_ConsumableItems << std::endl;
}

void Sekiro::Attack1(Player* enemy)
{
    InflictDamage(enemy);

    std::cout << "Sekiro Attacked!, Floating Passage!,  ";
    std::cout << "Damage Done: " << m_BaseDamage << std::endl << std::endl;
}

void Sekiro::Attack2(Player* enemy)
{
    std::cout << "Sekiro Attacked! Piercing Sabimaru!" << std::endl;
    std::cout << enemy->m_Name << " infected with poison, ";
    std::cout << enemy->m_Name << " vitality slowly degenrating..." << std::endl << std::endl;

    PoisonThread.push_back(std::async(std::launch::async, InflictPoisonEffectAsync, enemy));
}

void Sekiro::Heal()
{
    if (m_CurrentHealth == Max_Health)
    {
        std::cout << "Vitality is Full !" << std::endl << std::endl;
        return;
    }

    HandleHealingGourdUse();
}

void Sekiro::HandleHealingGourdUse()
{
    if (m_HealingGourds > 0 && m_CurrentHealth < Max_Health)
        RestoreHealthUsingHealingGourd();
    else
        std::cout << "Healing Gourd Empty !" << std::endl << std::endl; // meed to fix two times in a row healing by 2d array
}

void Sekiro::RestoreHealthUsingHealingGourd()
{
    m_CurrentHealth += m_VitalityGain;
    if (m_CurrentHealth > Max_Health) m_CurrentHealth = Max_Health;
    m_HealingGourds--;

    std::cout << "Sekiro Used Healing Gourd to Heal !" << std::endl;
    std::cout << "Sekiro's Health is now: " << m_CurrentHealth << std::endl << std::endl;
}

void Sekiro::ActivateSpecialAbility(Player* enemy, bool& shouldContinueTurn)
{
    if (m_HasSpiritEmblems)
    {
        DrawMortalBlade(enemy);
    }
    else
    {
        PerformRitualForSpiritEmblems();
        shouldContinueTurn = true;
    }
}

void Sekiro::DrawMortalBlade(Player* enemy)
{
    std::cout << "Sekiro used Mortal sword to Attack,  Damage Done: " << m_MortalSwordDamage << std::endl;
    std::cout << "" << std::endl;

    int enemyHealth = enemy->GetHealth();
    enemyHealth -= m_MortalSwordDamage;
    enemy->SetHealth(enemyHealth);

    m_HasSpiritEmblems = false;
}

void Sekiro::PerformRitualForSpiritEmblems()
{
    if (m_CurrentHealth >= (Max_Health / 2))
    {
        m_CurrentHealth = m_CurrentHealth - (m_CurrentHealth / m_RitualVitalityReduction);
        m_HasSpiritEmblems = true;

        std::cout << "Sekiro Perfomed Ritual!, Spirit emblems gained! " << std::endl;
        std::cout << "Mortal Sword can be used, Attack power 500% !" << std::endl;
        std::cout << "Press 'Z' to use to Attack with the Mortal Sword!, Sekiro's Turn Again!" << std::endl << std::endl;
    }
    else
        std::cout << "Not enough Vitality to perform Ritual!, Sekiro's turn again" << std::endl << std::endl;
}

void Sekiro::InflictPoisonEffectAsync(Player* enemy)
{
    int enemyHealth = enemy->GetHealth();
    for (int i = 0; i < s_DegenerateDuration && enemyHealth > 0; i++)
    {
        ApplyPoisonDamage(enemy);
        std::this_thread::sleep_for(1s);
    }

    DisplayPoisonEffectOutcome(enemy, enemyHealth);
}

void Sekiro::ApplyPoisonDamage(Player* enemy)
{
    int enemyHealth = enemy->GetHealth();
    if (enemyHealth > 0)
    {
        enemyHealth -= s_DegenerateDamage;
        enemy->SetHealth(enemyHealth);
    }
}

void Sekiro::DisplayPoisonEffectOutcome(Player* enemy, int enemyHealth)
{
    if (enemyHealth > 0)
    {
        std::cout << "--------------------------------" << std::endl;
        std::cout << "Poison Effect wore off, " << enemy->m_Name << "'s Vitality is now: " << enemyHealth << std::endl;
        std::cout << "" << std::endl;
    }
    else
        std::cout << enemy->m_Name << "'s Vitality is Zero Due to the Poisoning Effect!" << std::endl;
}