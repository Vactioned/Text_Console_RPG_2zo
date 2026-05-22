#include "Monster.h"
#include "Player.h"
#include <iostream>
#include <string>

using namespace std;

Monster::Monster(int maxhp, int attackPower, int SANPower, std::string name) {
    this->maxhp = maxhp;
    this->hp = maxhp;
    this->attackPower = attackPower;
    this->SANPower = SANPower;
    this->name = name;
}

void Monster::setname(std::string name) {
    this->name = name;
}

void Monster::TakeDamage(int damage) {
    hp -= damage;
    if (hp < 0) hp = 0;



    cout << name << "이" << damage << "피해를 입었습니다." << endl;
}

void Monster::Attack() {

    cout << name << "(이)가" << attackPower << "의 피해를 입혔습니다!" << endl;
}

//정신력 공격 구현
void Monster::SanAttack(Player* player, int SanDamage) {

    cout << name << "정신을 오염시켰습니다." << endl;

    if (player != nullptr) {
       // player-> 정신데미지 함수삽입
    }
}
