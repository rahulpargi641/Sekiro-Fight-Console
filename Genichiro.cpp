#include "Genichiro.h"

using namespace std::literals::chrono_literals;

std::vector <std::future<void>> HealingThread;
std::vector<std::future<void>> StunedThread;

Genichiro::Genichiro()
{
    m_Name = "Genichiro";
    m_Health = m_MaxHealth;
    m_BaseDamage = 50;
    m_ConsumableItems = 3; // Mist orbs

    bResurrected = false;
    m_Pellets = 3;
    bPelletInUse = false;
}

void Genichiro::TurnStats(Player* Enemy) const
{
    std::cout << "Genichiro's Turn!   ";
    std::cout << "Genichiro's Health: " << m_Health << "    ||    Enemy's Health: " << Enemy->GetHealth() <<"    ||    Pellets: " << m_Pellets << 
        "    ||    Consumables: " << m_ConsumableItems << std::endl;
}

void Genichiro::Attack1(Player* Enemy)
{
    DealDamage(Enemy);
    std::cout << "Genichiro Attacked!, Ashina Cross!,  ";
    std::cout << "Damage Done: " << m_BaseDamage << std::endl;
    std::cout << "" << std::endl;   
}

void Genichiro::Attack2(Player* Enemy)
{
    DealDamage(Enemy);
    std::cout << "Genochero Attacked!, Dragon Flash!,  ";  // yet to implement different Attack2 functionality
    std::cout << "Damage Done: " << m_BaseDamage << std::endl;
    std::cout << "" << std::endl;
}

void Genichiro::Heal()
{
    if (m_Health == m_MaxHealth)
    {
        std::cout << "Genichiro's Vitality is Full!" << std::endl;
        std::cout << "" << std::endl;
    }
    else if (m_Pellets > 0 && m_Health < m_MaxHealth)
    {
        if (!bPelletInUse)
        {
            bPelletInUse = true;  // Use the Pellet
            m_Pellets--;
            HealingThread.push_back(std::async(std::launch::async, RestoreVitality, &m_Health, &bPelletInUse));
            std::cout << "Genichiro Used Pallets to Heal !" << std::endl;
            std::cout << "Genichiro's Vitality Slowly Restoring...." << std::endl;
            std::cout << "" << std::endl;

        }
        else
        {
            std::cout << "Pallet already working, Increasing Vitality..." << std::endl;
            std::cout << "Genichiro's Health is = " << m_Health << std::endl;
            std::cout << "" << std::endl;
        }
    }
    else
    {
        std::cout << "All Pellets have been used!, no more pellets left!" << std::endl;
        std::cout << "" << std::endl;
    }
}


void Genichiro::ActivateSpecialAbility(Player* Enemy, bool& bKeepTurn)
{
    if (!bResurrected)
    {
        std::cout << "Genichero's Lightning Ability is acitvated only after Resurrection, Genichiro's turn again!" << std::endl;
        std::cout << "" << std::endl;
        bKeepTurn = true;
    }
    else
    {
        std::cout << "Genichiro Attacked! Lightning of Tomoe!" << std::endl;
        std::cout << "Damage Done: " << m_LightningDamage << std::endl;
        std::cout << Enemy->m_Name << " is Stunned by the Lightning..." << std::endl;
        std::cout << "" << std::endl;

        int EnemyHealth = Enemy->GetHealth();
        EnemyHealth -= m_LightningDamage;
        Enemy->SetHealth(EnemyHealth);
        bKeepTurn = true;
        StunedThread.push_back(std::async(std::launch::async, Stunned, Enemy, std::ref(bKeepTurn))); 
    }
}


void Genichiro::RestoreVitality(int* Health, bool* bPelletInUse)
{
    using namespace std::literals::chrono_literals;

    for (int i = 0; i < m_VitalityGainDuration; i++)
    {
        std::this_thread::sleep_for(1s); 
        *Health += m_VitalityGain;
        if (*Health > m_MaxHealth) *Health = m_MaxHealth;
        //std::cout << "Health inside the for loop: " << health << std::endl;
    }
    std::cout << "~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ " << std::endl;
    std::cout << "Genichiro's Health Increased after 15 seconds: " << *Health << std::endl;
    std::cout << "" << std::endl;
    *bPelletInUse = false;
}

void Genichiro::Stunned(Player* Enemy, bool& bKeepTurn)
{
    for (int i = 0; i < m_StunnedDuration; i++)
    {
        std::this_thread::sleep_for(1s);
    }
    bKeepTurn = false;
    std::cout << "Lightning Effect wore off!" << std::endl;
}

bool Genichiro::Dead()
{
    if (m_Health <= 0 && bResurrected) return true;
    else if (m_Health <= 0)
    {
        Resurrect();
        return false;
    }
    else
        return false;
}

void Genichiro::Resurrect()
{
    std::cout << "Genichiro's Vitality is zero!" << std::endl;
    std::cout << "Genichiro is resurrecting....." << std::endl;
    m_Health = m_MaxHealth / 3;
    bResurrected = true;
    std::this_thread::sleep_for(7s);

    std::cout << "Genichiro resurrcted!" << std::endl;
    std::cout << "Genichiro:- For the Glory of ashina ,  I will seize any manner of heretical strength, I will endure any burden. Behold - the Lightning of Tomoe.!" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Press 'Z' to use Lighting Attack!" << std::endl;
}
