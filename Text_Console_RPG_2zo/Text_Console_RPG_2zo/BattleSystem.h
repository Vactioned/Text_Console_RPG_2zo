#pragma once

#include "Player.h"
#include "Monster.h"
#include "Item.h"
#include "Skill.h"

void BattleStart(Player* player, Monster* monster);

int DamageCalculate(int attack, int defence);
