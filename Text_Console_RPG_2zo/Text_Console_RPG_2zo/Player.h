#pragma once

#include <iostream>
#include <string>

class Player
{
protected:

    std::string name;
    std::string job;
    int HP;
    int maxHP;
    int SAN;
    int maxSAN;
    int power;
    int defence;
    int sanDefence;
    int level;
    int Exp;
    int maxExp;

public:

    Player(std::string name, std::string job);

    virtual ~Player();

    std::string getName() const;
    std::string getJob() const;

    int getHP() const;
    int getmaxHP() const;
    int getSAN() const;
    int getmaxSAN() const;

    void setHP(int HP);
    void setmaxHP(int maxHP);
    void setSAN(int SAN);
    void setmaxSAN(int maxSAN);

    int getPower() const;
    int getDefence() const;
    int getSanDefence() const;

    void setPower(int power);
    void setDefence(int defence);
    void setSanDefence(int sanDefence);
  
    int getLevel() const;
    int getExp() const;
    int getmaxExp() const;

    void setLevel(int level);
    void setExp(int Exp);
    void setmaxExp(int maxExp);

    void printPlayerStatus() const;

    virtual void attack() = 0;
};

