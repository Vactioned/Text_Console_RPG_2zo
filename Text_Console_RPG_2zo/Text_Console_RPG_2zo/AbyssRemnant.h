#pragma once
#include "Monster.h"
#include "Player.h"
#include <cstdlib>
#include <iostream>



class AbyssRemnant : public Monster {
public:
    AbyssRemnant(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 10 + 1) + (playerlevel * 20), // 체력
            0,  // 공격력
            5, // 정신공격력
            15, // 몬스터 방어력
            "[심연의 잔재]") // 몬스터이름

    {
       
    }

    void Encounter() override {
        std::cout << "\n(출력대사) " << getName() << "이(가) 앞을 가로막습니다!\n" << std::endl;
    }

    int NormalAttack(Player* player) override {
        std::cout << getName() << "이 보라색 안개를 뿜어내며 당신의 온몸을 감쌉니다!" << std::endl;

        if (player != nullptr) {
            int sandamage = getSanPower() - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);
            std::cout << "스며드는 안개가 이성을 흐리며 정신을 " << sandamage << "만큼 붕괴시킵니다!." << std::endl;
        }
        return 0;
    }

    int SpecialAttack(Player* player) override {
        int powerreduction = 4;
        std::cout << getName() << "이 환각을 유발하는 짙은 심연의 가스를 폭발시킵니다" << std::endl;

        if (player != nullptr) {
            int currentpower = player->getPower();
            player->setPower(currentpower - powerreduction);
            std::cout << "지독한 안개로 인해 플레이어의 공격력이" << powerreduction << "만큼 감소합니다!" << std::endl;

            int finaldamage = (getSanPower() * 1.5) - player->getSanDefence();
            if (finaldamage < 1) finaldamage = 1;

            player->setSan(player->getSan() - finaldamage);
            std::cout << "극심한 두통과 함께 정신력이" << finaldamage << "만큼 오염됩니다!" << std::endl;
        }
        return 0;
    }
};
