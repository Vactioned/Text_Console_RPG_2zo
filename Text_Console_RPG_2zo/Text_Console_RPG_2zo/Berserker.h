#pragma once
#include "Player.h"
#include "Monster.h"
#include "Skill.h"
#include <string>

class Berserker : public Player
{
public:
    Berserker(std::string name, std::string job = "버서커");

    virtual ~Berserker() {}
    virtual void Attack(Monster* monster) override;
    virtual SkillData getSkillData(int skillIndex) override;
    virtual void useSkill(int skillIndex, Monster* monster, int& turn_cycle) override;
};

