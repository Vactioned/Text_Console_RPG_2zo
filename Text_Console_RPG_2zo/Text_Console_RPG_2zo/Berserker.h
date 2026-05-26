#pragma once
#include "Player.h"
#include "Monster.h"
#include <string>

class Berserker : public Player
{
public:
    Berserker(std::string name, std::string job = "버서커");

    virtual ~Berserker() {}

    virtual void Attack(Monster* monster) override;
};

