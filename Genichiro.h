#pragma once
#include "Player.h"
#include <thread>
#include <future>

class Genichiro : public Player
{
private:
    static const int m_MaxHealth = 300;
    static const int m_VitalityGain = 3;
    static const int m_VitalityGainDuration = 15;
    static const int m_StunnedDuration = 10;
    const int m_LightningDamage = 20;
    bool bResurrected;
    bool bPelletInUse;
    int m_Pellets;

public:
    Genichiro();
    void TurnStats(Player* Enemy) const override;
    void Attack1(Player* Enemy) override;
    void Attack2(Player* Enemy) override;
    void Heal() override;
    bool Dead() override;
    void ActivateSpecialAbility(Player* Enemy, bool& bKeepTurn) override;
    
private:
    void Resurrect();
    static void RestoreVitality(int* Health, bool* bPelletInUse);
    static void Stunned(Player* Enemy, bool& bKeepTurn);
    void UseMistOrbs(); // Yet to implement functionality
};




