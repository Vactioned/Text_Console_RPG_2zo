#pragma once
#include "Monster.h"
#include "Player.h"
#include <cstdlib>
#include <iostream>



class AltarGuardian : public Monster {
public:
    AltarGuardian(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 10 + 1) + (playerlevel * 20), // 체력
            rand() % (playerlevel * 5 + 1) + (playerlevel * 5),  // 공격력
            0, // 정신공격력
            5, // 몬스터 방어력
            "[제단의 파수병]") // 몬스터이름

    {
        
    }

    void Encounter() override {
        std::cout << "\n(출력대사) " << getName() << "이(가) 앞을 가로막습니다!\n" << std::endl;
    }

    int NormalAttack(Player* player) override {
        std::cout << getName() << "이(가) 육중한 발로 당신을 짓밟습니다!" << std::endl;
        int physdamage = 0;

        if (player != nullptr) {
            
            physdamage = getAttackPower() - player->getDefence();
            if (physdamage < 1) physdamage = 1;

            std::cout << "->" << physdamage << "의 물리 피해를 입었습니다!" << std::endl;
        }
        return physdamage;
    }

    int SpecialAttack(Player* player) override {

        std::cout << getName() << "이(가) 분노하며 주먹으로 땅을 내려칩니다!" << std::endl;
        int physdamage = 0;

        if (player != nullptr) {
            
            std::cout << ">>> 충격으로 인해 당신의 방어 장비가 파손되어 방어력이 5 감소합니다." << std::endl;
            player->setDefence(player->getDefence() - 5);

            
            physdamage = (getAttackPower() * 2) - player->getDefence();
            if (physdamage < 1) physdamage = 1;

            std::cout << "->" << physdamage << "의 물리 피해를 입었습니다!" << std::endl;



        }
        return physdamage;
    }
};

