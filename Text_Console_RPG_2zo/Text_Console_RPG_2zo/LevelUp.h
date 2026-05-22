#pragma once
#include "Player.h"

class Player;

class LevelUp
{
public:
    void AddExp(Player* player,int amount);
    void CheckLevelUp(Player* player);
    void PrintLevelInfo(Player* player);
    
private:
    
};
