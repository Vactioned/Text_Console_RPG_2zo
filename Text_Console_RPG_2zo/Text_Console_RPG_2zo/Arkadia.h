#pragma once
#include "Monster.h"
#include "Player.h"
#include <cstdlib>
#include <iostream>



class Arkadia : public Monster {

private:
    bool isCharging; //차징 상태 확인용
    
public:
    Arkadia(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 10 + 1) + (playerlevel * 20), // 체력
            rand() % (playerlevel * 5 + 1) + (playerlevel * 5),  // 공격력
            5, // 정신공격력
            5, // 몬스터 방어력
            "[도달자, 아르카디아]"), // 몬스터이름
            isCharging(false)


    {
    }

    int NormalAttack(Player* player) override {

        if (isCharging) return 0; // 차징 중에는 평타 안 침

        std::cout << getName() << "이 차원의 틈을 열어 공간을 베어버립니다!" << std::endl;

        if (player != nullptr) {
            // 정신력 공격을 평타와 별개로 상시 위협으로 포함
            int sandamage = getSanPower() / 2;
            player->setSan(player->getSan() - sandamage);
            std::cout << "-> 공간이 뒤틀리며 이성이 흔들립니다. 정신력이 " << sandamage << " 감소합니다!" << std::endl;
        }
        return getAttackPower();
    }

    int SpecialAttack(Player* player) override {
        if (!isCharging) {
            // 1단계 차징 준비
            isCharging = true;
            std::cout << getName() << "이 허공에서 검은 에너지를 응축합니다... [공허의 파멸 준비]" << std::endl;

            return 0;
        }
        else {
            // 2단계 방출
            isCharging = false;
            std::cout << getName() << "이 검은에너지를 폭발시킵니다!" << std::endl;

            int physdamage = getAttackPower() * 4;

            if (player != nullptr) {
                int sandamage = (getSanPower() * 3);
                player->setSan(player->getSan() - sandamage);
                std::cout << " 영혼까지 꿰뚫리는 고통! 정신력이 " << sandamage << " 감소합니다!" << std::endl;
            }
            return physdamage;
        }
        
    }
};

