#pragma once
#include "Monster.h"
#include "Player.h"
#include "LogManager.h"
#include <cstdlib>
#include <iostream>



class DimensionEye : public Monster {
public:
    DimensionEye(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 10 + 1) + (playerlevel * 24), // 체력
            0,  // 물리공격력은 없음
            15, // 정신공격력
            5, // 몬스터 방어력
            "[이계의 주시자]") // 몬스터이름

    {

    }

    void Encounter() override {
        std::cout << "\n시선이 느껴진다. 하나가 아니다. [이계의 주시자] 가 어둠 속에서 수많은 눈을 깜빡이며 당신을 바라본다.\n" << std::endl;
    }

    int NormalAttack(Player* player) override {
        LogManager::TypePrint(getName() + " 의 수많은 눈동자가 일제히 당신을 주시하기 시작합니다.", 5);

        if (player != nullptr) {

            int sandamage = getSanPower() - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);
            LogManager::TypePrint("\n기괴한 시선이 당신의 정신을 붕괴시킵니다. 정신력이 " + std::to_string(sandamage) + "만큼 감소합니다.", 5);
        }
        return 0;
    }
    //특수공격은 정신력데미지 증가
    int SpecialAttack(Player* player) override {
        LogManager::TypePrint(getName() + " 이(가) 거대한 눈을 부릅뜨고 당신을 주시합니다.", 5);

        if (player != nullptr) {
            int finalsandamage = (getSanPower() * 2) - player->getSanDefence();
            if (finalsandamage < 1) finalsandamage = 1;

            player->setSan(player->getSan() - finalsandamage);
            LogManager::TypePrint("\n강렬한 시선이 당신의 정신을 흩뜨립니다. 정신력이 " + std::to_string(finalsandamage) + "만큼 감소합니다.", 5);

        }
        return 0;
    }
};

