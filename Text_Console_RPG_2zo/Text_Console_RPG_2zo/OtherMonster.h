#pragma once
#include "Monster.h"
#include "Player.h"
#include <cstdlib>

class OtherMonster : public Monster {
public:
    OtherMonster(int playerlevel) //코드 간략화
        :Monster(rand() % ( playerlevel * 10 + 1) + (playerlevel * 20), // 체력
                 rand() % ( playerlevel * 5 + 1) + (playerlevel * 5),  // 공격력
                 5, // 정신공격력
                 5, // 몬스터 방어력
                 "몬스터 이름") // 몬스터이름

    {
    }

    void NormalAttack(Player* player) override {
        Monster::NormalAttack(player);
    }

    void SpecialAttack(Player* player) override {
        //각 몬스터의 특수공격 컨셉 구현칸
    }
};
