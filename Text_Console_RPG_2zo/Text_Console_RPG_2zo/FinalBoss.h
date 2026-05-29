#pragma once
#include "Monster.h"
#include "Player.h"
#include "Inventory.h"
#include "Item.h"
#include <cstdlib>
#include <iostream>

class FinalBoss : public Monster {
public:
    FinalBoss(int playerlevel);

    void Encounter() override;
    int NormalAttack(Player* player) override;
    int SpecialAttack(Player* player) override;
};

void RunFinalBossBattle(Player* player, Inventory<Item>& inventory);
