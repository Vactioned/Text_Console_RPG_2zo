#pragma once
#include "Player.h"
#include "Monster.h"
#include "Skill.h"
#include <string>

class Gambler : public Player
{
public:
    Gambler(std::string name, std::string job = "도박꾼");

    virtual ~Gambler() {}

    virtual void Attack(Monster* monster) override;
    virtual SkillData getSkillData(int skillIndex) override;
    virtual void useSkill(int skillIndex, Monster* monster, int& turn_cycle) override;
};
