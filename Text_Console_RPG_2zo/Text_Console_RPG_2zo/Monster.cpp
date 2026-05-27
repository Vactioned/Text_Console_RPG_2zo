#include "Monster.h"
#include "Player.h"
#include <iostream>
#include <string>

using namespace std;

Monster::Monster(int maxhp, int attackpower, int sanpower,int defence, std::string name) {
    this->maxhp = maxhp;
    this->hp = maxhp;
    this->attackpower = attackpower;
    this->sanpower = sanpower;
    this->defence = defence; //방어력 추가
    this->name = name;
}


int Monster::NormalAttack(Player* player) {
    
}
