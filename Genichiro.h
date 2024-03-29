#pragma once
#include "Player.h"
#include <thread>
#include <future>

using Duration = std::chrono::seconds;

class Genichiro : public Player
{
private:
    static const int s_MaxHealth = 300;
    static const int s_VitalityGain = 3;
    static const int s_VitalityGainDuration = 15;
    static const int s_StunnedDuration = 7;
    const Duration Resurrect_Time = Duration(7);

    bool m_HasResurrected;
    bool m_IsPelletInUse;
    int m_Pellets;
    int m_VitalityReduction;
    int m_LightningDamage;

public:
    Genichiro();
    void DisplayPlayerStats(Player* enemy) const override;
    void Attack1(Player* enemy) override;
    void Attack2(Player* enemy) override;
    void ActivateSpecialAbility(Player* enemy, bool& shouldContinueTurn) override;
    void Heal() override;
    bool IsDead() override;
    
private:
    void HandlePalletUse();
    void ConsumePallet();
    void RestoreHealthUsingPallet();
    void Resurrect();
    void PerformLightningAttack(Player*& enemy, bool& shouldContinueTurn);
    void InflictLightningDamage(Player* enemy);
    static void RestoreVitalityAsync(int* health, bool* isPalletInUse);
    static void StunEnemyAysnc(Player* enemy, bool& shouldContinueTurn);
};




