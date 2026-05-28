#pragma once

#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "Skill.h"
#include "Inventory.h"
#include "LevelUp.h"
#include <string>

void BattleStart(Player* player, Monster* monster, Inventory<Item>& inventory);
int  DamageCalculate(int attack, int defence);

class BattleSystem
{
private:
    int stageProgress = 0;

    bool RunSingleBattle(Player& player, Inventory<Item>& inventory, Monster* monster);
    bool StartBattle(Player& player, Inventory<Item>& inventory,
        const std::string& stage);

public:
    void EnterMissionMenu(Player& player, Inventory<Item>& inventory);
};
