#pragma once
#include "Player.h"
#include "Monster.h"
#include "Skill.h"
#include <string>

class Monk : public Player
{
public:
    Monk(std::string name, std::string job = "파계승");

    virtual ~Monk() {}

    virtual void Attack(Monster* monster) override;
    virtual SkillData getSkillData(int skillIndex) override;
    virtual void useSkill(int skillIndex, Monster* monster, int& turn_cycle) override;
};
