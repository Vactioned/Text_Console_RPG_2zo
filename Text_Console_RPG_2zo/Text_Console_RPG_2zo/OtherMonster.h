#pragma once
#include "Monster.h"
#include <cstdlib>

class OtherMonster : public Monster {
public:
    OtherMonster(int playerLevel) //코드 간략화
        :Monster(rand() % ( playerLevel * 10 + 1) + (playerLevel * 20), // 체력
                 rand() % ( playerLevel * 5 + 1) + (playerLevel * 5),  // 공격력
                 5, // 정신공격력
                 5, // 몬스터 방어력
                 "몬스터 이름") // 몬스터이름

    {

    }
};
