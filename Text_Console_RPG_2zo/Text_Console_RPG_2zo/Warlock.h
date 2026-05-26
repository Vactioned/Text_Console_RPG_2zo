#pragma once
#include "Player.h"
#include "Monster.h"
#include "Skill.h"
#include <string>

class Warlock : public Player
{
public:
    Warlock(std::string name, std::string job = "흑마법사");

    virtual ~Warlock() {}

    virtual void Attack(Monster* monster) override;
    virtual SkillData getSkillData(int skillIndex) override;
    virtual void useSkill(int skillIndex, Monster* monster, int& turn_cycle) override;
};

