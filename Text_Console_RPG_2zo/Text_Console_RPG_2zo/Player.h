#pragma once

#include "Monster.h"
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
    void setSan(int sna);
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
};

