#pragma once
#include "Monster.h"
#include "Player.h"
#include "LogManager.h"
#include <cstdlib>
#include <iostream>



class FanaticLeader : public Monster {
public:
    FanaticLeader(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 12 + 1) + (playerlevel * 28), // 체력
            rand() % (playerlevel * 4 + 1) + (playerlevel * 5),  // 공격력
            15, // 정신공격력
            5, // 몬스터 방어력
            "[광신도 간부]") // 몬스터이름

    {

    }

    void Encounter() override {
        std::cout << "\n일반 광신도와는 다른 무게감이 느껴진다. [광신도 간부] 가 불길한 기운이 감도는 기괴한 대검을 어깨에 걸친 채 당신을 내려다본다.\n" << std::endl;
    }


    int NormalAttack(Player* player) override {
        LogManager::TypePrint(getName() + " 이(가) 불길한 기운이 감도는 기괴한 대검을 치켜들며 광신의 주문을 외웁니다.", 5);
        int physdamage = 0;

        if (player != nullptr) {
            physdamage = getAttackPower() - player->getDefence();
            if (physdamage < 1) physdamage = 1;

            int sandamage = getSanPower() - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);
            LogManager::TypePrint("\n귀를 찢는 간부의 포효가 영혼을 흔들어 정신력이 " + std::to_string(sandamage) + "만큼 감소합니다.", 5);
        }
        return physdamage;
    }

    int SpecialAttack(Player* player) override {
        LogManager::TypePrint(getName() + " 이(가) 공허의 군주를 현신시키는 의식을 거행합니다.", 5);

        // 심연의 에너지를 통해 체력을 계속 회복
        setHp(getHp() + 20);
        LogManager::TypePrint("\n" + getName() + " 이(가) 심연의 에너지를 흡수하여 체력을 20 회복합니다.", 5);

        int physdamage = 0;

        if (player != nullptr) {
            physdamage = (getAttackPower()*2) - player->getDefence();
            if (physdamage < 1) physdamage = 1;

            int sandamage = (getSanPower() * 2) - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);
            LogManager::TypePrint("\n의식으로 강화된 공격을 실시합니다. 정신력이 " + std::to_string(sandamage) + "만큼 감소합니다.", 5);
        }

        return physdamage;
    }

};

