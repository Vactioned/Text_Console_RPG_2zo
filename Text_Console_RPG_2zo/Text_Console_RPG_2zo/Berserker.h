#pragma once
#include "Player.h"
#include "Monster.h"

class Berserker : public Player
{
public:
    Berserker(std::string name, std::string job);

    void Attack(Monster* monster);

};
