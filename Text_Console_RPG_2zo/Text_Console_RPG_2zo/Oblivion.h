#pragma once
#include "Monster.h"
#include "Player.h"
#include "LogManager.h"
#include <cstdlib>
#include <iostream>



class Oblivion : public Monster {
public:
    Oblivion(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 12 + 1) + (playerlevel * 30), // 체력
            0, // 공격력
            12, // 정신공격력
            20, // 방어력
            "[오블리비언]") //몬스터이름


    {

    }

    void Encounter() override {
        std::cout << "\n별자리인 줄 알았던 빛들이 깜빡이기 시작하며 나를 주시한다. [오블리비언] 이(가) 그 거대한 심연을 당신에게 겨눈다.\n" << std::endl;
    }

    int NormalAttack(Player* player) override {
        LogManager::TypePrint(getName() + " 이(가) 공간을 찢어발기며 허공에서 수많은 암흑 촉수를 꺼냅니다.", 5);

        if (player != nullptr) {
            int sandamage = getSanPower() - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);
            LogManager::TypePrint("\n멸망한 차원의 기억이 밀려오며 정신을 조각냅니다. 정신력이 " + std::to_string(sandamage) + "만큼 감소합니다.", 5);
        }
        return 0;
    }

    int SpecialAttack(Player* player) override {
        LogManager::TypePrint(getName() + " 이(가) 거대한 촉수에 달린 눈동자를 하나씩 개방하며 주변을 칠흑으로 물들이기 시작합니다.", 5);

        if (player != nullptr) {
            int finaldamage = (getSanPower() * 2) - player->getSanDefence();
            if (finaldamage < 1) finaldamage = 1;

            player->setSan(player->getSan() - finaldamage);
            LogManager::TypePrint("\n영혼이 통째로 뜯겨나가는 고통. 정신력이 " + std::to_string(finaldamage) + "만큼 감소합니다.", 5);

            int currentmonsterhp = getHp();
            setHp(currentmonsterhp + finaldamage);

            LogManager::TypePrint("\n" + getName() + " 이(가) 영혼을 흡수해 기력을 회복합니다.", 5);
        }
        return 0;
    }
};
