#pragma once
#include <iostream>

class Player
{
public:
    bool m_IsDead = false;
    std::string m_Name;

protected:
    int m_CurrentHealth;
    unsigned int m_VitalityGain; // Every player has different healing machanism
    unsigned int m_BaseDamage;
    unsigned int m_AdditionalDamage;  // If Attacked using Perfect form, You get Additional Damage
    int m_ConsumableItems; // Yet to Implement consume sugar candys functionality
  
protected:
    Player();
    void InflictDamage(Player* Enemy);

public:
    virtual void DisplayPlayerStats(Player* enemy) const = 0;
    virtual void Attack1(Player* enemy) = 0;
    virtual void Attack2(Player* enemy) = 0;
    virtual void ActivateSpecialAbility(Player* Enemy, bool& shouldContinueTurn) = 0;
    virtual void Heal() = 0;
    virtual void DisplayItemStats() const;
    virtual int GetHealth() const { return m_CurrentHealth; }
    virtual void SetHealth(int Health) { m_CurrentHealth = Health; }
    virtual bool IsDead();

private:
    int IsPerfectFormAttack();
};

