#pragma once
#include "GameInfo.h"

enum EPlayerType : unsigned char { EPT_Shinobi = 1, EPT_Samurai, EPT_RedKnight, EPT_SenpouPriest, EPT_OkamiWorrior };

enum class ETurn : unsigned char { ET_Player1 = 1, ET_Player2 };

ETurn Turn;

class GameInfo GameInfo;
const int Max_Players = 2;   // no. of Max Players allowed
static bool bStartFight = false;
static bool bKeepTurn = false;
static bool GameLoop = false;
static int PlayerCount = 0;
static char PlayerInput;

class Player;
static Player* CreatePlayer(int);
static void StartFight();
static void PlayerPlaying(Player* Player, class Player* Enemy);
static void ChangeTurn(ETurn& Turn);
static bool CheckIntegerInput(const char& Input);
static void DestroyPlayer(Player* Player[2]);









