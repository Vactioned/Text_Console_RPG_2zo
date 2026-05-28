#pragma once
#include "Monster.h"
#include "Player.h"
#include <cstdlib>
#include <iostream>



class FleshFusion : public Monster {
public:
    FleshFusion(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 10 + 1) + (playerlevel * 20), // 체력
            rand() % (playerlevel * 5 + 1) + (playerlevel * 5),  // 공격력
            5, // 정신공격력
            5, // 몬스터 방어력
            "[살점의 융합체]") // 몬스터이름

    {
    }

    int NormalAttack(Player* player) override {
        std::cout << getName() << "이 형태를 알아보기 힘든 촉수들을 채찍처럼 휘두릅니다!" << std::endl;
        int physdamage = getAttackPower();

        if (player != nullptr) {
            int sandamage = getSanPower() - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);
            std::cout << "융합체의 몸에서 나는 부패한 냄새가 이성을 마비시켜 정신력이 " << sandamage << "만큼 감소하였습니다!" << std::endl;
        }
        return physdamage;
    }

    int SpecialAttack(Player* player) override {
        std::cout << getName() << "이 몸을 팽창시키며 비명과 함께 살점을 사방으로 뿌립니다! " << std::endl;

       
        int physdamage = getAttackPower() * 2;

        if (player != nullptr) {

            int sandamage = (getSanPower() * 2) - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);
            std::cout << "-> 터져 나가는 살점들을 보고 구토가 치밀어 오릅니다! 정신력이 " << sandamage << "만큼 감소합니다!" << std::endl;
        }
        return physdamage;
    }
};

