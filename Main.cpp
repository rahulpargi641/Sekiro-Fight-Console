#include <iostream>
#include <string>
#include <memory>
#include <thread>
#include <future>
#include "Main.h"
#include "Player.h"
#include "Sekiro.h"
#include "Genichiro.h"
#include "GameInfo.h"

using namespace std::literals::chrono_literals;

int main()
{
    Player* A_Player[2];

    std::cout << "||||| TEXT BASED SEKIRO GAME |||||" << std::endl;
    GameInfo.DisplayInfo();
    
    for (int i = 0; i < Max_Players; i++)
    {
        std::cout << "Select the Player " << i + 1 << std::endl;
        std::cin >> PlayerInput;
        std::cout << "" << std::endl;

         if (CheckIntegerInput(PlayerInput)) A_Player[i] = CreatePlayer(int(PlayerInput - '0'));
         else
         {
             std::cout << "Wrong Key Pressed, Program Exited, Enter integer numbers (1 - 5) Play Again";
             break;
         }
    }

    if (PlayerCount == 2) GameLoop = true;
    else return 0; 

    std::cout << "Press 'Enter' to Start the Fight!!!" << std::endl;
    std::thread StartFightThread(StartFight);
    std::cin.get();

    StartFightThread.join();
    std::cout << "" << std::endl;
    std::cout << "FIGHT BEGINS..." << std::endl;

    Turn = ETurn::ET_Player1;
    while (GameLoop)
    {
        if (Turn == ETurn::ET_Player1)
        {
            PlayerPlaying(A_Player[0], A_Player[1]);    // Player[1] is the Enemy
            if (A_Player[1]->Dead())
            {
                std::cout << A_Player[1]->m_Name << " is Dead," << A_Player[0]->m_Name << " Won !" << "" << std::endl;
                break;
            }
            else
            {
                if (!bKeepTurn) ChangeTurn(Turn);
                else
                    bKeepTurn = false;
            } 
        }
        else
        {
            PlayerPlaying(A_Player[1], A_Player[0]);    // Player[0] is the Enemy
            if (A_Player[0]->Dead()) 
            {
                std::cout << A_Player[0]->m_Name << " is Dead, " << A_Player[1]->m_Name << " Won ! "<< "" << std::endl;
                break;
            }
            else
            {
                if (!bKeepTurn) ChangeTurn(Turn);
                else
                    bKeepTurn = false;
            }
        }
    }

    std::cout << " ||||| Game Over ||||| ";
    DestroyPlayer(A_Player);
}


Player* CreatePlayer(int Input)
{
    if (Input == EPT_Shinobi)
    {
        std::cout << "Use Full Screen Console window to see all the Player Information." << std::endl;
        std::cout << "" << std::endl;
        std::cout << "Player 1: " << GameInfo.Player1 << std::endl;
        std::cout << "" << std::endl;
      
        Sekiro* Sekiro = new class Sekiro();
        PlayerCount++;

        return Sekiro;
    }
    else if (Input == EPT_Samurai)
    {
        std::cout << "Use Full Screen Console window to see all the Player Information." << std::endl;
        std::cout << "" << std::endl;
        std::cout << "Player 2: " << GameInfo.Player2 << std::endl;
        std::cout << "" << std::endl;
        
        Genichiro* Genichiro = new class Genichiro;
        PlayerCount++;

        return Genichiro;
    }
    else if (Input == EPT_SenpouPriest)
    {
        std::cout << " Senpou priest is not available to choose yet!" << std::endl;
    }
    else if (Input == EPT_RedKnight)
    {
        std::cout << " Red Knight is not available to choose yet!" << std::endl;
    }
    else if (Input == EPT_OkamiWorrior)
    {
        std::cout << " Okami Worrior is not available to choose yet!" << std::endl;
    }
        return NULL; 
}

void PlayerPlaying(Player* Player, class Player* Enemy)
{
    Player->TurnStats(Enemy);

    std::cout << "Press 'A' to Attack1, 'D' to Attack2, 'H' to Heal, 'Z' to Activate Special Ability" << std::endl;
    std::cin >> PlayerInput;

    if (PlayerInput == 'A' || PlayerInput == 'a')
    {
        Player->Attack1(Enemy);
    }
    else if (PlayerInput == 'D' || PlayerInput == 'd')
    {
        Player->Attack2(Enemy);
    }
    else if (PlayerInput == 'H' || PlayerInput == 'h')
    {
        Player->Heal();
    }
    else if (PlayerInput == 'Z' || PlayerInput == 'z')
    {
        Player->ActivateSpecialAbility(Enemy, bKeepTurn);
    }
    else if (PlayerInput == 'I' || PlayerInput == 'i')
    {
        Player->ShowPlayerStats();
    }
    else
    {
        std::cout << "Invalid Input, Enter 'A' or 'H' or 'Z' or 'I'" << std::endl;
        std::cout << "" << std::endl;
        bKeepTurn = true;
    }       
}
       
void ChangeTurn(ETurn& Turn)
{
    if (Turn == ETurn::ET_Player1) Turn = ETurn::ET_Player2;
    else 
        Turn = ETurn::ET_Player1;
}

bool CheckIntegerInput(const char& Input)
{
    if (isdigit(Input)) return true;
    else
        return false;
}

void StartFight()
{
    while (!bStartFight)
    {
        if (std::cin.get()) bStartFight = true;
        else
            std::this_thread::sleep_for(1s);
    }
}

void DestroyPlayer(Player* Player[2]) // delete the memory
{
    for (int i = 0; i < 2; i++)
        delete Player[i];
}