#pragma once
#include "Player.h"
#include "Monster.h"
#include <string>

class Thief : public Player
{
public:
    Thief(std::string name, std::string job = "도적/약탈꾼");

    virtual ~Thief() {}

    virtual void Attack(Monster* monster) override;
};

