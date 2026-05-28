#pragma once
#include "Monster.h"
#include "Player.h"
#include <cstdlib>
#include <iostream>



class CorruptedKnight : public Monster {
public:
    CorruptedKnight(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 10 + 1) + (playerlevel * 20), // 체력
            rand() % (playerlevel * 5 + 1) + (playerlevel * 5),  // 공격력
            5, // 정신공격력
            5, // 몬스터 방어력
            "[부패한 기사단장]") // 몬스터이름

    {
    }

    int NormalAttack(Player* player) override {
        std::cout << getName() << "이(가) 타락한 검을 휘둘러 공간 자체를 갈라버립니다!" << std::endl;

        return getAttackPower();
    }

    int SpecialAttack(Player* player) override {
        std::cout << getName() << "이 눈을 번득이며 검에 공허의 기운을 담아 [죽음의 참격]을 준비합니다!" << std::endl;

        
        int physdamage = getAttackPower() * 2;

        if (player != nullptr) {
            
            int sandamage = (getSanPower() * 2);
            player->setSan(player->getSan() - sandamage);

            std::cout << "-> 검 끝에서 뿜어져 나오는 공허가 영혼을 갉아먹습니다! 정신력이 무려 " << sandamage << " 감소합니다!" << std::endl;
        }
        return physdamage;
    }
};
