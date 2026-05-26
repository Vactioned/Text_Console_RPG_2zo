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

void Monster::SetName(std::string name) {
    this->name = name;
}

void Monster::NormalAttack(Player* player) {
    cout << name << "(이)가 일반 공격을 시전합니다!" << endl;
    cout << "->" << attackpower << "의 일반 피해를 입혔습니다!." << endl;
    cout << "->" << name << "이(가) 정신을 오염시켜" << sanpower << "의 정신 피해를 입혔습니다" << endl;

    if (player != nullptr) {
        // player 쪽에 만들어둔 일반/정신피해 처리 함수 추가
    }
}
