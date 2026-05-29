#pragma once
#include "Monster.h"
#include "Player.h"
#include "LogManager.h"
#include <cstdlib>
#include <iostream>



class FleshFusion : public Monster {
public:
    FleshFusion(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 13 + 1) + (playerlevel * 32), // 체력
            rand() % (playerlevel * 4 + 1) + (playerlevel * 5),  // 공격력
            15, // 정신공격력
            5, // 몬스터 방어력
            "[살점의 융합체]") // 몬스터이름

    {

    }

    void Encounter() override {
        std::cout << "\n구역질 나는 부패의 냄새가 먼저 당도한다. [살점의 융합체] 가 역겹게 뒤엉킨 살덩이와 촉수를 질척이며 모습을 드러낸다.\n" << std::endl;
    }

    int NormalAttack(Player* player) override {
        LogManager::TypePrint(getName() + " 이(가) 형태를 알아보기 힘든 촉수들을 채찍처럼 휘두릅니다.", 5);
        int physdamage = 0;

        if (player != nullptr) {
            physdamage = getAttackPower() - player->getDefence();
            if (physdamage < 1) physdamage = 1;

            int sandamage = getSanPower() - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);
            LogManager::TypePrint("\n융합체의 몸에서 나는 부패한 냄새가 이성을 마비시킵니다. 정신력이 " + std::to_string(sandamage) + "만큼 감소합니다.", 5);
        }
        return physdamage;
    }

    int SpecialAttack(Player* player) override {
        LogManager::TypePrint(getName() + " 이(가) 몸을 팽창시키며 비명과 함께 살점을 사방으로 뿌립니다.", 5);


        int physdamage = 0;

        if (player != nullptr) {
            physdamage = (getAttackPower()*2.5) - player->getDefence();
            if (physdamage < 1) physdamage = 1;

            int sandamage = (getSanPower() * 2) - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);
            LogManager::TypePrint("\n터져 나가는 살점들을 보고 구토가 치밀어 오릅니다. 정신력이 " + std::to_string(sandamage) + "만큼 감소합니다.", 5);
        }
        return physdamage;
    }
};

