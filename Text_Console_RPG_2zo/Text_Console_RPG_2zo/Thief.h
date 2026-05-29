#pragma once
#include "Player.h"
#include "Monster.h"
#include "Skill.h"
#include <string>

class Thief : public Player
{
public:
    Thief(std::string name, std::string job = "도적");

    virtual ~Thief() {}

    virtual void Attack(Monster* monster) override;
    virtual SkillData getSkillData(int skillIndex) override;
    virtual void useSkill(int skillIndex, Monster* monster, int& turn_cycle) override;
};

