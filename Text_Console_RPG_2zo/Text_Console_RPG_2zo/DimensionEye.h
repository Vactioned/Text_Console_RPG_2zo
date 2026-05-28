#pragma once
#include "Monster.h"
#include "Player.h"
#include <cstdlib>
#include <iostream>



class DimensionEye : public Monster {
public:
    DimensionEye(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 10 + 1) + (playerlevel * 20), // 체력
            0,  // 물리공격력은 없음
            10, // 정신공격력
            5, // 몬스터 방어력
            "[이계의 주시자]") // 몬스터이름

    {
        std::cout << "\n(출력대사) " << getName() << "이(가) 앞을 가로막습니다!\n" << std::endl;
    }

    int NormalAttack(Player* player) override {
        std::cout << getName() << "수많은 눈동자가 일제히 당신을 주시하기 시작합니다." << std::endl;

        if (player != nullptr) {

            int sandamage = getSanPower() - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);
            std::cout << "기괴한 시선이 정신을" << sandamage << "만큼 붕괴시킵니다!" << std::endl;
        }
        return 0;
    }
    //특수공격은 정신력데미지 증가
    int SpecialAttack(Player* player) override {
        std::cout << getName() << "이 거대한 중앙의 눈을 부릅뜨며 정신을 붕괴시키기 시작합니다!" << std::endl;

        if (player != nullptr) {
            int finalsandamage = (getSanPower() * 1.5) - player->getSanDefence();
            if (finalsandamage < 1) finalsandamage = 1;

            player->setSan(player->getSan() - finalsandamage);
            std::cout << "눈앞이 흐려지며 극심한 정신적 스트레스가" << finalsandamage << "만큼 몰려옵니다!" << std::endl;
        
        }
        return 0;
    }
};

