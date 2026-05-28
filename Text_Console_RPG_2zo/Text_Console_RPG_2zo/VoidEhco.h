#pragma once
#include "Monster.h"
#include "Player.h"
#include <cstdlib>
#include <iostream>

//정신 공격력이 강력한게 포인트

class VoidEcho : public Monster {
public:
    VoidEcho(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 10 + 1) + (playerlevel * 20), // 체력
            rand() % (playerlevel * 5 + 1) + (playerlevel * 5),  // 공격력
            5, // 정신공격력
            5, // 몬스터 방어력
            "공허의 메아리") // 몬스터이름

    {
        std::cout << "\n(출력대사) " << getName() << "이(가) 앞을 가로막습니다!\n" << std::endl;
    }

    int NormalAttack(Player* player) override {
        std::cout << getName() << "의 비명이 당신의 정신을 관통합니다!" << std::endl;

        
       

        
        int finalSanDamage = getSanPower() - player->getSanDefence();
        if (finalSanDamage < 1) finalSanDamage = 1;

        player->setSan(player->getSan() - finalSanDamage);

        std::cout << ">>> 정신 방어력이 " << player->getSanDefence() << "만큼 공격을 흡수했습니다." << std::endl;
        std::cout << ">>> [정신력 감소] - " << finalSanDamage << std::endl;
        return 0;
    }

    int SpecialAttack(Player* player) override {
        std::cout << getName() << "이(가) 당신의 내면 깊은 곳의 공포를 실체화하여 쏟아붓습니다!" << std::endl;

        if (player != nullptr) {
            
            int sandamage = (getSanPower() * 5) - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);
            std::cout << ">>> 끔찍한 공포가 영혼을 짓누릅니다! [정신력 감소] - " << sandamage << std::endl;
        }
        return 0;
    }
};

