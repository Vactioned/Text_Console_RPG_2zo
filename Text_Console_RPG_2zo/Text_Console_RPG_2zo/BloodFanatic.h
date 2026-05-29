#pragma once
#include "Monster.h"
#include "Player.h"
#include "LogManager.h"
#include <cstdlib>
#include <iostream>



class BloodFanatic : public Monster {
public:
    BloodFanatic(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 12 + 1) + (playerlevel * 28), // 체력
            rand() % (playerlevel * 4 + 1) + (playerlevel * 5),  // 공격력
            12, // 정신공격력
            5, // 몬스터 방어력
            "[피의 광신도]") // 몬스터이름

    {

    }

    void Encounter() override {
        std::cout << "\n비릿한 냄새가 진동한다. [피의 광신도] 가 셀 수 없는 상처와 흉터로 뒤덮인 몸에서 피를 뚝뚝 흘리며 황홀한 표정으로 당신을 향해 선다.\n" << std::endl;
    }

    int NormalAttack(Player* player) override {
        LogManager::TypePrint(getName() + " 이(가) 광기에 가득 찬 눈으로 기괴한 주문을 외우며 피 묻은 단검을 휘두릅니다.", 5);
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
        LogManager::TypePrint(getName() + " 이(가) 알 수 없는 의식을 진행하며 자해를 시작합니다.", 5);

        setHp(getHp() - 15);
        LogManager::TypePrint("\n" + getName() + " 이(가) 자신의 피로 무기를 강화합니다. 체력이 15 감소합니다.", 5);

        int physdamage = 0;

        if (player != nullptr) {

            physdamage = (getAttackPower() * 2) - player->getDefence();
            if (physdamage < 1) physdamage = 1;

            int sandamage = (getSanPower() * 2) - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);
            LogManager::TypePrint("\n주변이 피로 뒤덮인 것처럼 보이는 환각이 닥칩니다. 정신력이 " + std::to_string(sandamage) + "만큼 감소합니다.", 5);

        }
        return physdamage;

    }
};
