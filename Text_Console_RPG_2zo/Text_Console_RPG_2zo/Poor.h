#pragma once
#include "Player.h"
#include "Monster.h"
#include <string>

class Poor : public Player
{
public:
    Poor(std::string name, std::string job = "부랑자");

    virtual ~Poor() {}

    virtual void Attack(Monster* monster) override;
};
