#include <iostream>
#include "LevelUp.h"

using namespace std;

void LevelUp::CheckLevelUp(Player* player)
{
    while (player -> getExp() >= player -> getmaxExp())
    {
        player -> setExp(player -> getExp() - player->getmaxExp());
        player -> setLevel(player -> getLevel() + 1);
    }
}

void LevelUp::AddExp(Player* player, int amount)
{
    player -> setExp(player->getExp() + amount);
    CheckLevelUp(player);
}

void LevelUp::PrintLevelInfo(Player* player)
{
    cout << "Level : " << player -> getLevel() << endl;
    cout << "Exp : " << player -> getExp() << " / " << player -> getmaxExp() << endl;
}
