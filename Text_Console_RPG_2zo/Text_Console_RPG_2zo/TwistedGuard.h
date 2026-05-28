#pragma once
#include "Monster.h"
#include "Player.h"
#include <cstdlib>
#include <iostream>



class TwistedGuard : public Monster {
public:
    TwistedGuard(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 10 + 1) + (playerlevel * 20), // 체력
            rand() % (playerlevel * 5 + 1) + (playerlevel * 5),  // 공격력
            5, // 정신공격력
            5, // 몬스터 방어력
            "[뒤틀린 호위병]") // 몬스터이름

    {
    }

    int NormalAttack(Player* player) override {
        std::cout << getName() << "이 녹슨 대검을 묵직하게 내리찍습니다!" << std::endl;

        
        int physdamage = getAttackPower();
        return physdamage;
    }

    int SpecialAttack(Player* player) override {
        std::cout << getName() << "이 방패로 전신을 가리고 강하게 돌진합니다! " << std::endl;

        // 돌진 공격이라 물리 대미지 강력하게!
        int physdamage = getAttackPower() * 1.5;

        if (player != nullptr) {
            int sandamage = getSanPower(); // 정신력 피해는 최소화
            player->setSan(player->getSan() - sandamage);
            std::cout << "-> 방패에 부딪힌 충격으로 정신이 아득해집니다. 정신력이 " << sandamage << "만큼 감소합니다!" << std::endl;
        }
        return physdamage;
    }
        
};

