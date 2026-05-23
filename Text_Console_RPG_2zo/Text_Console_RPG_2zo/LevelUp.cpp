#include <iostream>
#include "LevelUp.h"

using namespace std;

void LevelUp::CheckLevelUp(Player* player)
{
    while (player->getExp() >= player->getMaxExp())
    {
        int maxLevel = 10;
        if (maxLevel > player->getLevel())
        {
            player->setExp(player->getExp() - player->getMaxExp());
            player->setLevel(player->getLevel() + 1);
            player->setMaxHp(player->getMaxHp() + 20);
            player->setPower(player->getPower() + 5);
            player->setHp(player->getMaxHp());
            LevelUpEffect(player);
            
            int choice = 0;
            cout << "획득할 스탯을 선택해주세요" << endl;
            cout << "1. 방어력     2. 정신 방어력    3. 정신력 회복" << endl;
            cin >> choice;
            switch (choice)
            {
            case 1:
                player->setDefence(player->getDefence() + 2);
                break;

            case 2:
                player->setSanDefence(player->getSanDefence() + 1);
                break;

            case 3:
                player->setSan(player->getSan() + 20);
                break;

            default:
                cout << endl << "잘못 입력되었습니다. 다시 입력해주세요" << endl;
                break;
            }
        }
        else
        {
            player->setExp(player->getMaxExp());
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
