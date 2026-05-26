#pragma once
#include "Player.h"
#include "Monster.h"
#include <string>

class Gambler : public Player
{
public:
    Gambler(std::string name, std::string job = "도박꾼");

    virtual ~Gambler() {}

    virtual void Attack(Monster* monster) override;
};
