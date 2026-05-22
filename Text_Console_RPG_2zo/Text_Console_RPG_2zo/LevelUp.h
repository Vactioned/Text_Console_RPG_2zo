#pragma once
#include "Player.h"

class Player;

class LevelUp
{
public:
    void AddExp(Player* player,int amount);
    void CheckLevelUp(Player* player);

    // 테스트용
    void PrintLevelInfo(Player* player);
    
private:
    
};
