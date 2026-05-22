#pragma once
#include <iostream>
#include <string> 

class Player;

class Monster {
private:
    int hp;
    int maxhp;
    int attackPower;
    int SANPower;
    std::string name; 

public:
   
    Monster(int maxhp, int attackPower, int SANPower, std::string name);

    virtual ~Monster() {}

    
    void Attack(); // 몬스터가 주는 데미지
    void TakeDamage(int damage);
    void SanAttack(Player* player, int SanDamage); //몬스터가 플레이어에게 주는 정신공격데미지
    void setname(std::string name);

   
    int GetHp() { return hp; }
    int GetMaxhp() { return maxhp; }
    int GetAttackPower() { return attackPower; }
    int GetSANPower() { return SANPower; }
    std::string Getname() { return name; } 
};
