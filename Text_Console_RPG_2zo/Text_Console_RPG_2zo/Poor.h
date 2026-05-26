#pragma once
#include "Player.h"
#include "Monster.h"
#include "Skill.h"
#include <string>

class Poor : public Player
{
public:
    Poor(std::string name, std::string job = "부랑자");

    virtual ~Poor() {}

    virtual void Attack(Monster* monster) override;
    virtual SkillData getSkillData(int skillIndex) override;
    virtual void useSkill(int skillIndex, Monster* monster, int& turn_cycle) override;
};
