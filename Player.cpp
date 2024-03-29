#include "Player.h"


Player::Player()
{}

void Player::DisplayItemStats() const
{
    std::cout << "Health: " << m_CurrentHealth << std::endl;
    std::cout << "Consumable";
}

void Player::InflictDamage(Player* other)
{
    int currentHealth = other->GetHealth();
    if (currentHealth > 0)
    {
        if (IsPerfectFormAttack())
            currentHealth -= m_BaseDamage + m_AdditionalDamage;
        else
            currentHealth -= m_BaseDamage;

        other->SetHealth(currentHealth);
    }
}

int Player::IsPerfectFormAttack()
{
    srand((unsigned)time(NULL));
    int perfectAttackChance = rand() % 100 + 1;  // Generate random number from 1 to 100
    if (perfectAttackChance <= 20) //20% chance
    {
        std::cout << "Attacked Using Perfect Form, Additional Damage: " << m_AdditionalDamage;
        return true;
    }
    else
        return false;
}

bool Player::IsDead()
{
    m_IsDead = (m_CurrentHealth <= 0);
    return m_IsDead;
}
