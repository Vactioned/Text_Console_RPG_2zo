#pragma once
#include "Monster.h"
#include "Player.h"
#include <cstdlib>
#include <iostream>

class Unknown : public Monster {
public:
    Unknown(int playerlevel)
        : Monster(9999, // 
            999,  
            99,   
            99,   
            "[????]")
    {
    }

    int NormalAttack(Player* player) override {
        std::cout << "[????]이(가) 손가락을 튕기자 현실이 붕괴합니다." << std::endl;

        
        int damage = 999;
        std::cout << "-> " << damage << "의 피해를 입었습니다. " << std::endl;

        return damage;
    }

    int SpecialAttack(Player* player) override {
        std::cout << "[????]이(가) 당신의 존재를 부정합니다." << std::endl;

        if (player != nullptr) {
            
            player->setSan(0);
            std::cout << ">>> 당신의 정신이 완전히 붕괴되었습니다. " << std::endl;
        }

        return 9999; 
    }
};
