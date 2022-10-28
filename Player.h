#pragma once
#include <iostream>

class Player
{
public:
    bool bDead = false;
    std::string m_Name;

protected:
    bool bPerfectForm = false;
    int m_Health;
    unsigned int m_VitalityGain; // Every player has different healing machanism
    unsigned int m_BaseDamage;
    unsigned int m_AdditionalDamage;  // If Attacked using Perfect form, You get Additional Damage
    int m_ConsumableItems; // Yet to Implement consume sugar candys functionality
  
    Player();
    void DealDamage(Player* Enemy);
    int AdditionalDamage(); 

public:
    virtual void TurnStats(Player* Enemy) const = 0;
    virtual void Attack1(Player* Enemy) = 0;
    virtual void Attack2(Player* Enemy) = 0;
    virtual void ActivateSpecialAbility(Player* Enemy, bool& bKeepTurn) = 0;
    virtual void Heal() = 0;
    virtual void ShowPlayerStats() const;
    virtual int GetHealth() const { return m_Health; }
    virtual void SetHealth(int Health) { m_Health = Health; }
    virtual bool Dead();

};

