#pragma once
#include "Player.h"
#include <future>
#include <thread>

class Sekiro : public Player
{
private:
    static const int m_Degenerate = 3;
    static const int m_DegenerateDuration = 15;
    const int m_MaxHealth = 200;
    bool bSpiritEmblems;
    bool bDrawMortalBlade;
    int m_HealingGourds;
    unsigned int m_MortalSwordDamage;

public:
    Sekiro();
    void TurnStats(Player* Enemy) const override;
    void Attack1(Player* Enemy) override;
    void Attack2(Player* Enemy) override;
    void ActivateSpecialAbility(Player* Enemy, bool& bKeepTurn) override;
    void Heal() override;

private:
    void PerformRitual();
    void DrawMortalBlade(Player* Enemy);
    static void InflictPoisonEffect(Player* Enemy);
    void BiteUngoSugar(); // Yet to Implement functionality
};

