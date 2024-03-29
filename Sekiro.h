#pragma once
#include "Player.h"
#include <future>
#include <thread>

static std::vector <std::future<void>> PoisonThread;

class Sekiro : public Player
{
private:
    static const int s_DegenerateDamage = 3;
    static const int s_DegenerateDuration = 15;
    const int Max_Health = 200;

    bool m_HasSpiritEmblems;
    bool m_CanDrawMortalBlade;
    int m_HealingGourds;
    unsigned int m_RitualVitalityReduction;
    unsigned int m_MortalSwordDamage;

public:
    Sekiro();
    void DisplayPlayerStats(Player* enemy) const override;
    void Attack1(Player* enemy) override;
    void Attack2(Player* enemy) override;
    void ActivateSpecialAbility(Player* Enemy, bool& shouldContinueTurn) override;
    void Heal() override;

private:
    void HandleHealingGourdUse();
    void RestoreHealthUsingHealingGourd();
    void PerformRitualForSpiritEmblems();
    void DrawMortalBlade(Player* enemy);
    static void InflictPoisonEffectAsync(Player* enemy);
    static void ApplyPoisonDamage(Player* enemy);
    static void DisplayPoisonEffectOutcome(Player* enemy, int enemyHealth);
};

