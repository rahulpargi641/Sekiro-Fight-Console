#include "GameInfo.h"

void GameInfo::DisplayCharacterSelection() const
{
    std::cout << "||||| TEXT BASED SEKIRO GAME |||||" << std::endl;

    std::cout << "There are 2 different players to choose from:  1. Sekiro | 2. Genichiro |" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "To select the sekiro Press '1'" << std::endl;
    std::cout << "To select the Genichiro Press '2'" << std::endl;
    std::cout << "" << std::endl;
}

void GameInfo::DisplayPlayerInfo(int PlayerNo) const
{}
