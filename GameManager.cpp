#include "GameManager.h"
#include "Sekiro.h"
#include "Genichiro.h"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std::literals::chrono_literals;

void GameManager::StartGame() 
{
    DisplayCharacterSelection();
    SelectPlayers();

    if (IsGameReadyToStart()) 
    {
        StartFight();
        ExecuteGame();
        DisplayGameOver();
    }
}

void GameManager::DisplayCharacterSelection() 
{
    m_GameInfo.DisplayCharacterSelection();
}

void GameManager::SelectPlayers() 
{
    for (int i = 0; i < Max_Players; i++) {
        std::cout << "Select the Player " << i + 1 << std::endl;
        std::cin >> m_UserInput;
        std::cout << "" << std::endl;

        if (IsInputInteger(m_UserInput))
        {
            m_Players[i] = CreatePlayer(static_cast<int>(m_UserInput - '0'));
        }
        else 
        {
            std::cout << "Wrong Key Pressed, Program Exited, Enter integer numbers (1 - 5) Play Again";
            break;
        }
    }
}

bool GameManager::IsGameReadyToStart() 
{
    if (m_PlayerCount == 2) 
    {
        m_IsGameRunning = true;
        return true;
    }
    return false;
}

void GameManager::StartFight() 
{
    std::cout << "Press 'Enter' to Start the Fight!!!" << std::endl;
    std::thread startFightThread(&GameManager::StartFightThread, this);
    std::cin.get();
    startFightThread.join();
    std::cout << "" << std::endl;
    std::cout << "FIGHT BEGINS..." << std::endl;
}

void GameManager::ExecuteGame() 
{
    m_CurrentTurn = ETurn::Player1;

    while (m_IsGameRunning)
    {
        Player* currentPlayer = m_Players[m_CurrentTurn == ETurn::Player1 ? 0 : 1];
        Player* opponentPlayer = m_Players[m_CurrentTurn == ETurn::Player1 ? 1 : 0];

        HandlePlayerTurn(currentPlayer, opponentPlayer);

        if (opponentPlayer->IsDead())
        {
            std::cout << opponentPlayer->m_Name << " is Dead, " << currentPlayer->m_Name << " Won ! " << std::endl;
            break;
        }

        SwitchTurn();
    }

    DestroyPlayers();
}

void GameManager::DisplayGameOver() 
{
    std::cout << " ||||| Game Over ||||| ";
}

void GameManager::StartFightThread() 
{
    while (!m_HasFightStarted) 
    {
        if (std::cin.get())
            m_HasFightStarted = true;
        else
            std::this_thread::sleep_for(1s);
    }
}

Player* GameManager::CreatePlayer(int input) 
{
    Player* player = nullptr;
    switch (input) 
    {
    case static_cast<int>(EPlayerType::Shinobi):
        std::cout << "Use Full Screen Console window to see all the Player Information." << std::endl << std::endl;
        std::cout << "Player 1: " << m_GameInfo.Player1 << std::endl << std::endl;
        player = new Sekiro();
        m_PlayerCount++;
        break;
    case static_cast<int>(EPlayerType::Samurai):
        std::cout << "Use Full Screen Console window to see all the Player Information." << std::endl << std::endl;
        std::cout << "Player 2: " << m_GameInfo.Player2 << std::endl << std::endl;
        player = new Genichiro();
        m_PlayerCount++;
        break;
    case static_cast<int>(EPlayerType::SenpouPriest):
        std::cout << " Senpou priest is not available to choose yet!" << std::endl;
        break;
    case static_cast<int>(EPlayerType::RedKnight):
        std::cout << " Red Knight is not available to choose yet!" << std::endl;
        break;
    case static_cast<int>(EPlayerType::OkamiWorrior):
        std::cout << " Okami Worrior is not available to choose yet!" << std::endl;
        break;
    }
    return player;
}

void GameManager::HandlePlayerTurn(Player* player, Player* opponentPlayer) 
{
    player->DisplayPlayerStats(opponentPlayer);

    std::cout << "Press 'A' to Attack1, 'D' to Attack2, 'H' to Heal, 'Z' to Activate Special Ability" << std::endl;
    std::cin >> m_UserInput;

    switch (m_UserInput) 
    {
    case 'A':
    case 'a':
        player->Attack1(opponentPlayer);
        break;
    case 'D':
    case 'd':
        player->Attack2(opponentPlayer);
        break;
    case 'H':
    case 'h':
        player->Heal();
        break;
    case 'Z':
    case 'z':
        player->ActivateSpecialAbility(opponentPlayer, m_ShouldContinueTurn);
        break;
    case 'I':
    case 'i':
        player->DisplayItemStats();
        break;
    default:
        std::cout << "Invalid Input, Enter 'A' or 'H' or 'Z' or 'I'" << std::endl;
        std::cout << "" << std::endl;
        m_ShouldContinueTurn = true;
        break;
    }
}

void GameManager::SwitchTurn() 
{
    m_CurrentTurn = (m_CurrentTurn == ETurn::Player1) ? ETurn::Player2 : ETurn::Player1;
}

bool GameManager::IsInputInteger(const char& input)
{
    return std::isdigit(input);
}

void GameManager::DestroyPlayers() 
{
    for (int i = 0; i < 2; i++)
        delete m_Players[i];
}