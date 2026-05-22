#pragma once
#include "Monster.h"
#include <cstdlib>

class OtherMonster : public Monster {
public:
    OtherMonster(int playerLevel) 
        :Monster( rand() % (playerLevel * 30 - playerLevel * 20 + 1 ) + (playerLevel *20), // 체력
            rand() % (playerLevel *10 - playerLevel * 5 + 1) + (playerLevel * 5)           // 공격력
            , 5 , // 정신공격력                                                          
            "몬스터 이름") // 몬스터이름
        
    {

    }
};
