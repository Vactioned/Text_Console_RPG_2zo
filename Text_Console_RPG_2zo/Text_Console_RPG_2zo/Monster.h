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

    virtual int NormalAttack(Player* player) = 0;  // 1.일반공격 

    virtual int SpecialAttack(Player* player) = 0; // 2. 특수공격

     

    void setHp(int newhp) {
        this->hp = newhp;
        if (this->hp < 0) this->hp = 0;
        if (this->hp > maxhp) this->hp = maxhp;
      
    }

    void setMaxHp(int newmaxhp) {
        this->maxhp = newmaxhp;
        if (this->maxhp < 1) this->maxhp = 1;
    }
    void setAttackPower(int newattackpower) {
        this->attackpower = newattackpower;
        if (this->attackpower < 0) this->attackpower = 0;
    }

    void setSanPower(int newsanpower) {
        this->sanpower = newsanpower;
        if (this->sanpower < 0) this->sanpower = 0;
    }

    void setDefence(int newdefence) {
        this->defence = newdefence;
        if (this->defence < 0) this->defence = 0;
    }

    void SetName(std::string name) {
        this->name = name;
    }

   
    int getHp() { return hp; }
    int getMaxhp() { return maxhp; }
    int getAttackPower() { return attackpower; }
    int getSanPower() { return sanpower; }
    int getDefence() { return defence; }
    std::string getName() { return name; } 
};
