#include "Monster.h"
#include "Player.h"
#include <iostream>
#include <string>

using namespace std;

Monster::Monster(int maxhp, int attackpower, int sanpower,int defense, std::string name) {
    this->maxhp = maxhp;
    this->hp = maxhp;
    this->attackpower = attackpower;
    this->sanpower = sanpower;
    this->defense = defense; //방어력 추가
    this->name = name;
}

void Monster::SetName(std::string name) {
    this->name = name;
}

void Monster::TakeDamage(int damage) {
    int finaldamage = damage - this->defense; // 데미지에서 방어력 뺴기 = 최종데미지

    if (finaldamage < 1) {
        finaldamage = 1; //최소데미지 1
    }
    hp -= finaldamage;
    if (hp < 0) hp = 0;



    cout << name << "이" << finaldamage << "피해를 입었습니다." << endl;
}

void Monster::Attack() {

    cout << name << "(이)가" << attackpower << "의 피해를 입혔습니다!" << endl;
}

//정신력 공격 구현
void Monster::SanAttack(Player* player, int sandamage) {

    cout << name << "정신을 오염시켰습니다." << endl;

    if (player != nullptr) {
       // player-> 정신데미지 함수삽입
    }
}
