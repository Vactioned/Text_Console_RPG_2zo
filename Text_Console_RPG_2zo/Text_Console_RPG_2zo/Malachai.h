#pragma once
#include "Monster.h"
#include "Player.h"
#include <cstdlib>
#include <iostream>



class Malachai : public Monster {
public:
    Malachai(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 10 + 1) + (playerlevel * 20), // 체력
            rand() % (playerlevel * 5 + 1) + (playerlevel * 5),  // 공격력
            5, // 정신공격력
            5, // 몬스터 방어력
            "교주[말라카이]") // 몬스터이름

    {
    }

    int NormalAttack(Player* player) override {
        std::cout << getName() << "가 공허의 에너지가 흘러넘치는 지팡이를 휘두르며 파멸의 주문을 외우기 시작합니다!" << std::endl;
        int physdamage = 0;

        if (player != nullptr) {

            physdamage = getAttackPower() - player->getDefence();
            if (physdamage < 1) physdamage = 1;

            int sandamage = getSanPower() - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);
            std::cout << "교주의 무자비한 저주가 온몸을 감싸며 정신력이 " << sandamage << "만큼 감소하였습니다!" << std::endl;
            std::cout << "->" << physdamage << "의 물리 피해를 입었습니다!" << std::endl;
        }
        return physdamage;
    }

    int SpecialAttack(Player* player) override {
        std::cout << getName() << "가 하늘을 향해 지팡이를 치켜들며 광기 어린 목소리로 외칩니다!" << std::endl;
        std::cout << "\"너희의 피를 바쳐라!!! 전부 심연의 제물이 될 것이다!\"" << std::endl;

        // 보스라 피흡량이 상당히 높음
        setHp(getHp() + 30);
        std::cout << "-> " << getName() << "가 주위의 핏빛 에너지를 흡수하여 HP를 30 회복합니다!" << std::endl;

       // 데미지도 3배
        int physdamage = 0;


        if (player != nullptr) {
            physdamage = (getAttackPower()*3) - player->getDefence();
            if (physdamage < 1) physdamage = 1;

            int sandamage = (getSanPower() * 2) - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);
            std::cout << "->  [교주의 위압감] 공포로 인해 심장이 터질 것 같습니다! 정신력이 " << sandamage << "만큼 감소합니다!" << std::endl;
            std::cout << "->" << physdamage << "의 물리 피해를 입었습니다!" << std::endl;
        }
        return physdamage;
    }
};

