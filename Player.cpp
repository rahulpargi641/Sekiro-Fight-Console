#include "Player.h"


Player::Player()
{
}

void Player::ShowPlayerStats() const
{
    std::cout << "Health: " << m_Health << std::endl;
    std::cout << "Consumable";
}

void Player::DealDamage(Player* Enemy)
{
    int EnemyHealth = Enemy->GetHealth();
    if (!EnemyHealth <= 0)
    {
        if (bPerfectForm)
            EnemyHealth -= m_BaseDamage + AdditionalDamage();
        else
        EnemyHealth -= m_BaseDamage;

        Enemy->SetHealth(EnemyHealth);
    }
}

int Player::AdditionalDamage()
{
    srand((unsigned)time(NULL));
    int MoreDamage = rand();
    MoreDamage = rand() % 100 + 1;  //Generate random number 1 to 100
    if (MoreDamage <= 20) //20% chance
    {
        bPerfectForm = true;
        std::cout << "Attacked Using Perfect Form, Additional Damage: " << MoreDamage;
        return MoreDamage;
    }
    else
    return 0;
}

bool Player::Dead()
{
    if (m_Health <= 0)
    {
        bDead = true;
        return true;
    }
    else
        return false;
}
