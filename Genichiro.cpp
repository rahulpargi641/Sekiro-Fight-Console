#include "Genichiro.h"

using namespace std::literals::chrono_literals;

std::vector <std::future<void>> healingThread;
std::vector <std::future<void>> stunedThread;

Genichiro::Genichiro()
{
    m_Name = "Genichiro";
    m_CurrentHealth = s_MaxHealth;
    m_BaseDamage = 50;
    m_AdditionalDamage = 10;
    m_ConsumableItems = 3; // Mist orbs

    m_HasResurrected = false;
    m_IsPelletInUse = false;

    m_Pellets = 3;
    m_VitalityReduction = 3;
    m_LightningDamage = 20;
}

void Genichiro::DisplayPlayerStats(Player* enemy) const
{
    std::cout << "Genichiro's Turn!   ";
    std::cout << "Genichiro's Health: " << m_CurrentHealth << "    ||    Enemy's Health: " << enemy->GetHealth() <<"    ||    Pellets: " << m_Pellets << 
        "    ||    Consumables: " << m_ConsumableItems << std::endl;
}

void Genichiro::Attack1(Player* enemy)
{
    InflictDamage(enemy);

    std::cout << "Genichiro Attacked!, Ashina Cross!,  ";
    std::cout << "Damage Done: " << m_BaseDamage << std::endl << std::endl;
}

void Genichiro::Attack2(Player* enemy)
{
    InflictDamage(enemy);

    std::cout << "Genochero Attacked!, Dragon Flash!,  ";  // yet to implement different Attack2 functionality
    std::cout << "Damage Done: " << m_BaseDamage << std::endl << std::endl;
}

void Genichiro::Heal()
{
    if (m_CurrentHealth == s_MaxHealth)
    {
        std::cout << "Genichiro's Vitality is Full!" << std::endl << std::endl;
        return;
    }

    HandlePalletUse();
}

void Genichiro::HandlePalletUse()
{
    if (m_Pellets > 0 && m_CurrentHealth < s_MaxHealth)
        ConsumePallet();
    else
        std::cout << "All Pellets have been used!, no more pellets left!" << std::endl << std::endl;
}

void Genichiro::ConsumePallet()
{
    if (!m_IsPelletInUse)
    {
        RestoreHealthUsingPallet();
    }
    else
    {
        std::cout << "Pallet already working, Increasing Vitality..." << std::endl;
        std::cout << "Genichiro's Health is = " << m_CurrentHealth << std::endl << std::endl;
    }
}

void Genichiro::RestoreHealthUsingPallet()
{
    m_IsPelletInUse = true;  // Use the Pellet
    m_Pellets--;
    healingThread.push_back(std::async(std::launch::async, RestoreVitalityAsync, &m_CurrentHealth, &m_IsPelletInUse));

    std::cout << "Genichiro Used Pallets to Heal !" << std::endl;
    std::cout << "Genichiro's Vitality Slowly Restoring...." << std::endl << std::endl;
}

void Genichiro::RestoreVitalityAsync(int* currentHealth, bool* isPalletInUse)
{
    for (int i = 0; i < s_VitalityGainDuration; i++)
    {
        std::this_thread::sleep_for(1s);

        *currentHealth += s_VitalityGain;
        if (*currentHealth > s_MaxHealth) *currentHealth = s_MaxHealth;
    }

    std::cout << "~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ " << std::endl;
    std::cout << "Genichiro's Health Increased after 15 seconds: " << *currentHealth << std::endl << std::endl;
    *isPalletInUse = false;
}

void Genichiro::ActivateSpecialAbility(Player* enemy, bool& shouldContinueTurn)
{
    if (!m_HasResurrected)
    {
        std::cout << "Genichero's Lightning Ability can only be activated after Resurrection, Genichiro's turn again!" << std::endl << std::endl;
        shouldContinueTurn = true;
    }
    else
        PerformLightningAttack(enemy, shouldContinueTurn);
}

void Genichiro::PerformLightningAttack(Player*& enemy, bool& shouldContinueTurn)
{
    std::cout << "Genichiro Attacked! Lightning of Tomoe!" << std::endl;
    std::cout << "Damage Done: " << m_LightningDamage << std::endl;
    std::cout << enemy->m_Name << " is Stunned by the Lightning..." << std::endl << std::endl;

    InflictLightningDamage(enemy);

    shouldContinueTurn = true;
    stunedThread.push_back(std::async(std::launch::async, StunEnemyAysnc, enemy, std::ref(shouldContinueTurn)));  // Stun the enemy
}

void Genichiro::InflictLightningDamage(Player* enemy)
{
    int enemyHealth = enemy->GetHealth();
    enemyHealth -= m_LightningDamage;
    enemy->SetHealth(enemyHealth);
}

void Genichiro::StunEnemyAysnc(Player* Enemy, bool& shouldContinueTurn)
{
    for (int i = 0; i < s_StunnedDuration; i++)
        std::this_thread::sleep_for(1s);

    shouldContinueTurn = false;
    std::cout << "Lightning Effect wore off!" << std::endl;
}

bool Genichiro::IsDead()
{
    if (m_CurrentHealth <= 0 && m_HasResurrected) return true;

    if (m_CurrentHealth <= 0)
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

    m_HasResurrected = true;
    m_CurrentHealth = s_MaxHealth / m_VitalityReduction;
    std::this_thread::sleep_for(Resurrect_Time);

    std::cout << "Genichiro resurrcted!" << std::endl;
    std::cout << "Genichiro:- For the Glory of ashina ,  I will seize any manner of heretical strength, I will endure any burden. Behold - the Lightning of Tomoe.!" << std::endl << std::endl;
    std::cout << "Press 'Z' to use Lighting Attack!" << std::endl;
}
