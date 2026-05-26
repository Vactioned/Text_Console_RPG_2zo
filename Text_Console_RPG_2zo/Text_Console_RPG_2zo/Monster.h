#pragma once
#include <iostream>
#include <string> 

class Player;

class Monster {
private:
    int hp;
    int maxhp;
    int attackpower;
    int sanpower;
    int defence;
    std::string name; 

public:
   
    Monster(int maxhp, int attackpower, int sanpower,int defense, std::string name);

    virtual ~Monster() {}

    virtual void NormalAttack(Player* player);      // 1.일반공격 

    virtual void SpecialAttack(Player* player) = 0; // 2. 특수공격

    void SetName(std::string name); //이름변경용 함수

   
    int getHp() { return hp; }
    int getMaxhp() { return maxhp; }
    int getAttackPower() { return attackpower; }
    int getSanPower() { return sanpower; }
    int getDefence() { return defence; }
    std::string getName() { return name; } 
};
