#pragma once
#include "Monster.h"
#include "Player.h"
#include "LogManager.h"
#include <cstdlib>
#include <iostream>

class Unknown : public Monster {
public:
    Unknown(int playerlevel)
        : Monster(9999, //
            999,
            99,
            99,
            "[????]")
    {

    }

    void Encounter() override {
        std::cout << "\n깨어진 하늘의 파편 너머로, 가늠조차 되지 않는 것이 강림하기 시작한다. 그 압도적인 존재감 앞에 나의 존재는 한없이 희미해졌고, 무력함이 전신을 적셨다. 스스로를 기만하며 떨리는 손으로 무기를 쥐어든다. [????] 가 세계의 종언을 고한다.\n" << std::endl;
    }

    int NormalAttack(Player* player) override {
        LogManager::TypePrint("[????] 이(가) 손가락을 튕기자 현실이 붕괴합니다.", 5);

        int damage = 0;
        if (player != nullptr) {
            damage = player->getHp() / 2;
            if (damage < 1) damage = 1;
        }

        return damage;
    }

    int SpecialAttack(Player* player) override {
        LogManager::TypePrint("[????] 이(가) 당신의 존재를 부정합니다.", 5);

        int damage = 0;
        if (player != nullptr) {
            player->setSan(1);
            LogManager::TypePrint("\n당신의 정신이 완전히 붕괴되었습니다.", 5);

            damage = player->getHp() / 2;
            if (damage < 1) damage = 1;
        }

        return damage;
    }
};
