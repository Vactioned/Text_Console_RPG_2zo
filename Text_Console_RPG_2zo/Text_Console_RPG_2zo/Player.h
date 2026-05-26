#pragma once

#include "Monster.h"
#include "Skill.h"
#include <iostream>
#include <string>

class Player
{
protected:

    std::string name;
    std::string job;
    int hp;
    int maxhp;
    int san;
    int maxsan;
    int power;
    int defence;
    int sandefence;
    int level;
    int exp;
    int maxexp;

private:

    int attackBoostAmount;
    bool attackBoostApplied;

public:

    Player(std::string name, std::string job);

    std::string getName() const;
    std::string getJob() const;

    int getHp() const;
    int getMaxHp() const;
    int getSan() const;
    int getMaxSan() const;

    void setHp(int hp);
    void setMaxHp(int maxhp);
    void setSan(int san);
    void setMaxSan(int maxsan);

    int getPower() const;
    int getDefence() const;
    int getSanDefence() const;

    void setPower(int power);
    void setDefence(int defence);
    void setSanDefence(int sandefence);
  
    int getLevel() const;
    int getExp() const;
    int getMaxExp() const;

    void setLevel(int level);
    void setExp(int Exp);
    void setMaxExp(int maxExp);

    void PrintPlayerStatus() const;

    virtual void Attack(Monster* monster) = 0;

    // 스킬 정보 반환
    virtual SkillData getSkillData(int skillIndex) = 0;

    // 스킬 사용(액티브 스킬)
    virtual void useSkill(int skillIndex, Monster* monster, int& turn_cycle) = 0;

    int getAttackBoostAmount() const;
    bool isAttackBoostApplied() const;

    void setAttackBoostAmount(int amount);
    void setAttackBoostApplied(bool value);
};

