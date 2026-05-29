#pragma once
#include "Monster.h"
#include "Player.h"
#include "LogManager.h"
#include <cstdlib>
#include <iostream>



class AbyssRemnant : public Monster {
public:
    AbyssRemnant(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 10 + 1) + (playerlevel * 24), // 체력
            0,  // 공격력
            10, // 정신공격력
            15, // 몬스터 방어력
            "[심연의 잔재]") // 몬스터이름

    {

    }

    void Encounter() override {
        std::cout << "\n보라빛 안개가 발끝부터 스며든다. 형체라고 부르기도 어려운 것, [심연의 잔재] 가 서서히 당신을 에워싼다.\n" << std::endl;
    }

    int NormalAttack(Player* player) override {
        LogManager::TypePrint(getName() + " 이(가) 뿜어낸 보라색 안개가 당신을 감쌉니다.", 5);

        if (player != nullptr) {
            int sandamage = getSanPower() - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);
            LogManager::TypePrint("\n스며드는 안개가 이성을 흐리며 정신을 붕괴시킵니다. 정신력이 " + std::to_string(sandamage) + "만큼 감소합니다.", 5);
        }
        return 0;
    }

    int SpecialAttack(Player* player) override {
        int powerreduction = 4;
        LogManager::TypePrint(getName() + " 이(가) 환각을 유발하는 짙은 심연의 가스를 폭발시킵니다.", 5);

        if (player != nullptr) {
            int currentpower = player->getPower();
            player->setPower(currentpower - powerreduction);
            LogManager::TypePrint("\n안개가 눈을 가려 공격의 위력이 떨어집니다. 공격력이 " + std::to_string(powerreduction) + "만큼 감소합니다.", 5);

            int finaldamage = (getSanPower() * 1.5) - player->getSanDefence();
            if (finaldamage < 1) finaldamage = 1;

            player->setSan(player->getSan() - finaldamage);
            LogManager::TypePrint("\n극심한 두통으로 정신을 차리기 어렵습니다. 정신력이 " + std::to_string(finaldamage) + "만큼 떨어집니다.", 5);
        }
        return 0;
    }
};
