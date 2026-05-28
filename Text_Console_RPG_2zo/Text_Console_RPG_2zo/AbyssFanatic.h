#pragma once
#include "Monster.h"
#include "Player.h"
#include "LogManager.h"
#include <cstdlib>
#include <iostream>



class AbyssFanatic : public Monster {
public:
    AbyssFanatic(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 12 + 1) + (playerlevel * 28), // 체력
            rand() % (playerlevel * 4 + 1) + (playerlevel * 5),  // 공격력
            12, // 정신공격력
            5, // 몬스터 방어력
            "[심연의 광신도]") // 몬스터이름

    {

    }

    void Encounter() override {
        std::cout << "\n도저히 사람처럼 보기 힘든 무언가가 다가온다. [심연의 광신도] 가 온몸에 새겨진 문양을 드러내며 기괴한 웃음을 흘린다.\n" << std::endl;
    }

    int NormalAttack(Player* player) override {
        LogManager::TypePrint(getName() + " 이(가) 광기에 가득 찬 눈으로 기괴한 주문을 외우며 주먹을 휘두릅니다.", 5);
        int physdamage = 0;

        if (player != nullptr) {

            physdamage = getAttackPower() - player->getDefence();
            if (physdamage < 1) physdamage = 1;

            int sandamage = getSanPower() - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);
            LogManager::TypePrint("\n귀를 찢는 광신도의 주문이 이성을 오염시켜 정신력이 " + std::to_string(sandamage) + "만큼 감소합니다.", 5);
        }
        return physdamage;
    }

    int SpecialAttack(Player* player) override {
        LogManager::TypePrint(getName() + " 이(가) 알 수 없는 의식을 진행하며 영혼을 제물로 바칩니다.", 5);

        setHp(getHp() - 15);
        LogManager::TypePrint("\n" + getName() + " 이(가) 영혼을 대가로 힘을 증폭시킵니다. 체력이 15 감소합니다.", 5);

        int physdamage = 0;

        if (player != nullptr) {

            physdamage = (getAttackPower() * 2) - player->getDefence();
            if (physdamage < 1) physdamage = 1;

            int sandamage = (getSanPower() * 2) - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);
            LogManager::TypePrint("\n암흑의 환각이 몰려와 정신력이 " + std::to_string(sandamage) + "만큼 감소합니다.", 5);

        }
        return physdamage;

    }
};

