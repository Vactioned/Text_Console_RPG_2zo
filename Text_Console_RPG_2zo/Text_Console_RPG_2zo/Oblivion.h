#pragma once
#include "Monster.h"
#include "Player.h"
#include <cstdlib>
#include <iostream>



class Oblivion : public Monster {
public:
    Oblivion(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 10 + 1) + (playerlevel * 20), // 체력
            0, // 공격력
            5, // 정신공격력
            20, // 방어력
            "[오블리비언]") //몬스터이름
            

    {
    }

    int NormalAttack(Player* player) override {
        std::cout << getName() << "이 공간을 찢어발기며 허공에서 수많은 암흑 촉수를 꺼냅니다!" << std::endl;

        if (player != nullptr) {
            int sandamage = getSanPower() - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);
            std::cout << "-> 멸망한 차원의 기억이 밀려오며 정신력이 " << sandamage << "만큼 조각납니다!" << std::endl;
        }
        return 0;
    }

    int SpecialAttack(Player* player) override {
        std::cout << getName() << "이 거대한 촉수에 달린 눈동자를 하나씩 개방하며 주변을 칠흑으로 물들이기 시작합니다!" << std::endl;

        if (player != nullptr) {
            int finaldamage = (getSanPower() * 1.6) - player->getSanDefence();
            if (finaldamage < 1) finaldamage = 1;

            player->setSan(player->getSan() - finaldamage);
            std::cout << "영혼이 통쨰로 뜯겨나가는 고통! 정신력이" << finaldamage << "감소합니다" << std::endl;

            int currentmonsterhp = getHp();
            setHp(currentmonsterhp + finaldamage);

            std::cout << "영혼 흡수 " << getName() << "이 빼앗은 정신력을 본인의 체력으로 흡수합니다!" << std::endl;
        }
        return 0;
    }
};
