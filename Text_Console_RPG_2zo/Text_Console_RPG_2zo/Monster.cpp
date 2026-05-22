#include "Monster.h"
#include "Player.h"
#include <iostream>
#include <string>

Monster::Monster(int maxhp, int attackPower, int SANPower) {
    this->maxhp = maxhp;
    this->hp = maxhp;
    this->attackPower = attackPower;
    this->SANPower = SANPower;
}

void Monster::setname(std::string name) {
    this->name = name;
}

void Monster::TakeDamage(int damage) {
    hp -= damage;
    if (hp < 0) hp = 0;

    std::cout << name <<"(이)가" << damage << "의 피해를 입었습니다.";
}
void Monster::Attack() {

    std::cout << name << "(이)가" << attackPower << "의 피해를 입혔습니다!";
}

//정신력 공격 구현
void Monster::SanAttack(Player* player, int SanDamage) {

    std::cout << name << "정신을 오염시켰습니다.";

    if (player != nullptr) {
       // player-> 정신데미지 함수삽입
    }
}
