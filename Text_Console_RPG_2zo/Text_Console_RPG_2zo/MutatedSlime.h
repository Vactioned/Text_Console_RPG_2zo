#pragma once
#include "Monster.h"
#include "Player.h"
#include <cstdlib>
#include <iostream>

class MutatedSlime : public Monster {
public:
    MutatedSlime(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 15 + 1) + (playerlevel * 25), // 체력
            rand() % (playerlevel * 3 + 1) + (playerlevel * 3),  // 공격력
            0, // 정신공격력
            8, // 몬스터 방어력
            "[변이된 슬라임]") // 몬스터이름

    {
        std::cout << "\n(출력대사) " << getName() << "이(가) 앞을 가로막습니다!\n" << std::endl;
    }

    int NormalAttack(Player* player) override {
        std::cout << getName() << "이 끈적이는 촉수를 후려칩니다!" << std::endl;
        int damage = getAttackPower() - player->getDefence();
        if (damage < 1) damage = 1;


        if (player != nullptr) {
         
            std::cout << "->" << damage << "의 데미지를 입혔습니다!" << std::endl;
        }
        return damage;
    }

    int SpecialAttack(Player* player) override {
        int initialdamage = getAttackPower() * 1.2; //부식액으로 살짝 더 강한 피해
        int armorreduction = 3; //깎아낼 플레이어 방어력 수치
        int damage = 0;

        std::cout << getName() << "이(가) 몸을 부풀리더니 강산성 점액을 사방으로 뿜어냅니다!" << std::endl;
        std::cout << "강한산성에 의해 플레이어의 방어력이 녹아내립니다!(방어력 " << armorreduction << "감소)" << std::endl;

        if (player != nullptr) {
            int currentarmor = player->getDefence();
            player->setDefence(currentarmor - armorreduction);

            damage = initialdamage - player->getDefence();
            if (damage < 1) damage = 1;

            
            std::cout << "->" << damage << "의 물리 피해를 입혔습니다!" << std::endl;
        }
        return damage;
    }
};

