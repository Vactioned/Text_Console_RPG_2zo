#pragma once
#include "Monster.h"
#include "Player.h"
#include <cstdlib>
#include <iostream>



class BloodFanatic : public Monster {
public:
    BloodFanatic(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 10 + 1) + (playerlevel * 20), // 체력
            rand() % (playerlevel * 5 + 1) + (playerlevel * 5),  // 공격력
            5, // 정신공격력
            5, // 몬스터 방어력
            "[피의 광신도]") // 몬스터이름

    {
        std::cout << "\n(출력대사) " << getName() << "이(가) 앞을 가로막습니다!\n" << std::endl;
    }

    int NormalAttack(Player* player) override {
        std::cout << getName() << "이 광기에 가득 찬 눈으로 기괴한 주문을 외우며 피 묻은 단검을 휘두릅니다!" << std::endl;
        int physdamage = 0;

        if (player != nullptr) {
            physdamage = getAttackPower() - player->getDefence();
            if (physdamage < 1) physdamage = 1;

            int sandamage = getSanPower() - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);
            std::cout << "귀를 찢는 광신도의 주문이 이성을 오염시켜 정신력이" << sandamage << "만큼 감소하였습니다!" << std::endl;
            std::cout << "->" << physdamage << "의 물리 피해를 입었습니다!" << std::endl;
        }
        return physdamage;
    }

    int SpecialAttack(Player* player) override {
        std::cout << getName() << "이 알수없는 의식을 진행하며 자해를 하기 시작합니다!" << std::endl;

        setHp(getHp() - 15);
        std::cout << "->" << getName() << "이 자신의 피로 무기를 강화합니다! (몬스터 HP 15감소)" << std::endl;

        int physdamage = 0;

        if (player != nullptr) {

            physdamage = (getAttackPower() * 2) - player->getDefence();
            if (physdamage < 1) physdamage = 1;

            int sandamage = (getSanPower() * 2) - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);
            std::cout << "->" << "환각에 걸려 주변 모든 것이 피에 휩쓸려 보여 정신력이" << sandamage << "만큼 감소합니다!" << std::endl;
            std::cout << "->" << physdamage << "의 물리 피해를 입었습니다!" << std::endl;

        }
        return physdamage;

    }
};
