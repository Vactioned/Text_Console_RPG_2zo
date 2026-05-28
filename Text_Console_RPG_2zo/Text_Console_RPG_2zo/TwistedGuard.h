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

    void Encounter() override {
        std::cout << "\n(출력대사) " << getName() << "이(가) 앞을 가로막습니다!\n" << std::endl;
    }

    int NormalAttack(Player* player) override {
        std::cout << getName() << "이 녹슨 대검을 묵직하게 내리찍습니다!" << std::endl;
        int physdamage = 0;

        if (player != nullptr) {
           
            physdamage = getAttackPower() - player->getDefence();
            if (physdamage < 1) physdamage = 1;

            std::cout << "->" << physdamage << "의 물리 피해를 입었습니다!" << std::endl;
        }
        return physdamage;
    }

    int SpecialAttack(Player* player) override {
        std::cout << getName() << "이 방패로 전신을 가리고 강하게 돌진합니다! " << std::endl;

 
        int physdamage = 0;

        if (player != nullptr) {
            physdamage = (getAttackPower() * 2) - player->getDefence();
            if (physdamage < 1) physdamage = 1;

            
            int sandamage = getSanPower() - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);

            std::cout << "-> 방패에 부딪힌 충격으로 정신이 아득해집니다. 정신력이 " << sandamage << "만큼 감소합니다!" << std::endl;
            std::cout << "->" << physdamage << "의 물리 피해를 입었습니다!" << std::endl;
        }
        return physdamage;
    }
        
};

