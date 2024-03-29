#pragma once
#include "GameInfo.h"
#include "Player.h"

class GameManager
{
private:
    enum class EPlayerType : unsigned char { Shinobi = 1, Samurai, RedKnight, SenpouPriest, OkamiWorrior };
    enum class ETurn : unsigned char { Player1 = 1, Player2 };

    const int Max_Players = 2;

    bool m_HasFightStarted = false;
    bool m_ShouldContinueTurn = false;
    bool m_IsGameRunning = false;

    GameInfo m_GameInfo;
    ETurn m_CurrentTurn;
    Player* m_Players[2] = { nullptr };
    int m_PlayerCount = 0;
    char m_UserInput;

public:
    void StartGame();

private:
    void DisplayCharacterSelection();
    void SelectPlayers();
    bool IsGameReadyToStart();
    void StartFight();
    void ExecuteGame();
    void DisplayGameOver();
    Player* CreatePlayer(int input);
    void HandlePlayerTurn(Player* player, Player* opponentPlayer);
    void SwitchTurn();
    bool IsInputInteger(const char& input);
    void DestroyPlayers();
    void StartFightThread();
};










