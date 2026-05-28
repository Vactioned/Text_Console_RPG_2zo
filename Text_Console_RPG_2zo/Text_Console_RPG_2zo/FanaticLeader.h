#pragma once
#include "Monster.h"
#include "Player.h"
#include <cstdlib>
#include <iostream>



class FanaticLeader : public Monster {
public:
    FanaticLeader(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 10 + 1) + (playerlevel * 20), // 체력
            rand() % (playerlevel * 5 + 1) + (playerlevel * 5),  // 공격력
            5, // 정신공격력
            5, // 몬스터 방어력
            "[광신도 간부]") // 몬스터이름

    {
    }

    int NormalAttack(Player* player) override {
        std::cout << getName() << "이 불길한 기운이 감도는 집행검을 치켜들며 광신의 주문을 외웁니다!" << std::endl;
        int physdamage = 0;

        if (player != nullptr) {
            physdamage = getAttackPower() - player->getDefence();
            if (physdamage < 1) physdamage = 1;

            int sandamage = getSanPower() - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);
            std::cout << "귀를 찢는 간부의 포효가 영혼을 흔들어 정신력이 " << sandamage << "만큼 감소하였습니다!" << std::endl;
        }
        return physdamage;
    }   

    int SpecialAttack(Player* player) override {
        std::cout << getName() << "이 공허의 군주를 현신시키는 의식을 거행합니다!" << std::endl;

        // 심연의 에너지를 통해 체력을 계속 회복
        setHp(getHp() + 20);
        std::cout << "->" << getName() << "이 심연의 에너지를 흡수하여 HP를 20 회복합니다!" << std::endl;

        int physdamage = 0;

        if (player != nullptr) {
            physdamage = (getAttackPower()*2) - player->getDefence();
            if (physdamage < 1) physdamage = 1;

            int sandamage = (getSanPower() * 2) - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);
            std::cout << "-> 암흑의 환각이 시야를 가려 정신력이 " << sandamage << "만큼 감소합니다!" << std::endl;
            std::cout << "->" << physdamage << "의 물리 피해를 입었습니다!" << std::endl;
        }

        return physdamage;
    }
        
};

