#include <iostream>
#include "LevelUp.h"

using namespace std;

void LevelUp::CheckLevelUp(Player* player)
{
    while (player->getExp() >= player->getmaxExp())
    {
        int maxLevel = 10;
        if (maxLevel >= player->getLevel())
        {
        player->setExp(player->getExp() - player->getmaxExp());
        player->setLevel(player->getLevel() + 1);
        player->setmaxHP(player->getLevel() * 20);
        player->setPower(player->getLevel() * 5);
        player->setHP(player->getmaxHP());
        break;
        }
        break;
    }
}

void LevelUp::AddExp(Player* player, int amount)
{
    player->setExp(player->getExp() + amount);
    CheckLevelUp(player);
}

// 테스트용
void LevelUp::PrintLevelInfo(Player* player)
{
    cout << "Level : " << player->getLevel() << endl;
    cout << "Exp : " << player->getExp() << " / " << player->getmaxExp() << endl;
}
