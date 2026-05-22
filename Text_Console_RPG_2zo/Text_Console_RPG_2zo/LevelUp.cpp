#include <iostream>
#include "LevelUp.h"

using namespace std;

void LevelUp::CheckLevelUp(Player* player)
{
    while (player->getExp() >= player->getmaxExp())
    {
        int maxLevel = 10;
        if (maxLevel > player->getLevel())
        {
            player->setExp(player->getExp() - player->getmaxExp());
            player->setLevel(player->getLevel() + 1);
            player->setmaxHP(player->getmaxHP() + 20);
            player->setPower(player->getPower() + 5);
            player->setHP(player->getmaxHP());
            LevelUpEffect(player);
            player->setSAN(player->getmaxSAN());
        }
        else
        {
            player->setExp(player->getmaxExp());
            break;
        }
    }
}


void LevelUp::AddExp(Player* player, int amount)
{
    player->setExp(player->getExp() + amount);
    CheckLevelUp(player);
}

void LevelUp::LevelUpEffect(Player* player)
{
    cout << "================" << endl;
    cout << "   LEVLE UP!!" << endl;
    cout << "   Lv " << player->getLevel() - 1 << "->" << "Lv " << player->getLevel() << endl;
    cout << "   HP + 20" << endl;
    cout << "   공격력 + 5" << endl;
    cout << "================" << endl;
}

// 테스트용
void LevelUp::PrintLevelInfo(Player* player)
{
    cout << "Level : " << player->getLevel() << endl;
    cout << "Exp : " << player->getExp() << " / " << player->getmaxExp() << endl;
}
