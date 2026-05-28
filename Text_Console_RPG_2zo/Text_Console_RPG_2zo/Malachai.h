#pragma once
#include "Monster.h"
#include "Player.h"
#include "LogManager.h"
#include <cstdlib>
#include <iostream>



class Malachai : public Monster {
public:
    Malachai(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 15 + 1) + (playerlevel * 35), // 체력
            rand() % (playerlevel * 5 + 1) + (playerlevel * 6),  // 공격력
            18, // 정신공격력
            5, // 몬스터 방어력
            "[교주, 말라카이]") // 몬스터이름

    {

    }

    void Encounter() override {
        std::cout << "\n낮고 확신에 찬 목소리가 공간을 채운다. [교주, 말라카이] 가 공허의 기운이 흘러넘치는 지팡이를 짚으며 천천히 걸어온다. 발을 내디딜 때마다 공기가 무겁게 가라앉고, 숨이 막히는 압박감이 온몸을 짓누른다.\n" << std::endl;
    }

    int NormalAttack(Player* player) override {
        LogManager::TypePrint(getName() + " 가 공허의 에너지가 흘러넘치는 지팡이를 휘두르며 파멸의 주문을 외우기 시작합니다.", 5);
        int physdamage = 0;

        if (player != nullptr) {

            physdamage = getAttackPower() - player->getDefence();
            if (physdamage < 1) physdamage = 1;

            int sandamage = getSanPower() - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);
            LogManager::TypePrint("\n교주의 무자비한 저주가 온몸을 감싸며 정신력이 " + std::to_string(sandamage) + "만큼 감소합니다.", 5);
        }
        return physdamage;
    }

    int SpecialAttack(Player* player) override {
        LogManager::TypePrint(getName() + " 가 하늘을 향해 지팡이를 치켜들며 광기 어린 목소리로 외칩니다.", 5);
        LogManager::TypePrint("\n\"너희의 피를 바쳐라. 전부 심연의 제물이 될 것이다.\"", 5);

        // 보스라 피흡량이 상당히 높음
        setHp(getHp() + 30);
        LogManager::TypePrint("\n" + getName() + " 가 주위의 핏빛 에너지를 흡수하여 체력을 30 회복합니다.", 5);

       // 데미지도 3배
        int physdamage = 0;

        if (player != nullptr) {
            physdamage = (getAttackPower()*3) - player->getDefence();
            if (physdamage < 1) physdamage = 1;

            int sandamage = (getSanPower() * 2) - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);
            LogManager::TypePrint("\n공포가 당신의 심장을 옥죄입니다. 정신력이 " + std::to_string(sandamage) + "만큼 감소합니다.", 5);
        }
        return physdamage;
    }
};

