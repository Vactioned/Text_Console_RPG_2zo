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
    int defense;
    std::string name; 

public:
   
    Monster(int maxhp, int attackpower, int sanpower,int defense, std::string name);

    virtual ~Monster() {}

    
    void Attack(); // 몬스터가 주는 데미지
    void TakeDamage(int damage);
    void SanAttack(Player* player, int SanDamage); //몬스터가 플레이어에게 주는 정신공격데미지
    void SetName(std::string name);

   
    int getHp() { return hp; }
    int getMaxhp() { return maxhp; }
    int getAttackPower() { return attackpower; }
    int getSanPower() { return sanpower; }
    int getDefense() { return defense; }
    std::string getName() { return name; } 
};
