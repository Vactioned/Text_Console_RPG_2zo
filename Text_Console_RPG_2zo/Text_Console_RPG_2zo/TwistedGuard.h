#pragma once
#include "Monster.h"
#include "Player.h"
#include "LogManager.h"
#include <cstdlib>
#include <iostream>



class TwistedGuard : public Monster {
public:
    TwistedGuard(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 13 + 1) + (playerlevel * 32), // 체력
            rand() % (playerlevel * 4 + 1) + (playerlevel * 5),  // 공격력
            15, // 정신공격력
            5, // 몬스터 방어력
            "[침식된 파수병]") // 몬스터이름

    {

    }

    void Encounter() override {
        std::cout << "\n무겁고 불규칙한 발소리가 가까워진다. [침식된 파수병] 이(가) 방패를 앞세운 채 뒤틀린 몸을 이끌고 모습을 드러낸다.\n" << std::endl;
    }

    int NormalAttack(Player* player) override {
        LogManager::TypePrint(getName() + " 이(가) 녹슨 대검을 묵직하게 내리찍습니다.", 5);
        int physdamage = 0;

        if (player != nullptr) {

            physdamage = getAttackPower() - player->getDefence();
            if (physdamage < 1) physdamage = 1;
        }
        return physdamage;
    }

    int SpecialAttack(Player* player) override {
        LogManager::TypePrint(getName() + " 이(가) 방패로 전신을 가리고 강하게 돌진합니다.", 5);


        int physdamage = 0;

        if (player != nullptr) {
            physdamage = (getAttackPower() * 2.5) - player->getDefence();
            if (physdamage < 1) physdamage = 1;

            int sandamage = getSanPower() - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);

            LogManager::TypePrint("\n방패에 부딪힌 충격으로 정신이 아득해집니다. 정신력이 " + std::to_string(sandamage) + "만큼 감소합니다.", 5);
        }
        return physdamage;
    }

};

