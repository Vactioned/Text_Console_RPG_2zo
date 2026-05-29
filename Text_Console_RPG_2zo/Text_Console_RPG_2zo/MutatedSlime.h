#pragma once
#include "Monster.h"
#include "Player.h"
#include "LogManager.h"
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

    }

    void Encounter() override {
        std::cout << "\n코를 찌르는 부식의 냄새가 밀려온다. [변이된 슬라임] 이(가) 끈적한 몸을 꿈틀거리며 모습을 드러낸다.\n" << std::endl;
    }

    int NormalAttack(Player* player) override {
        LogManager::TypePrint(getName() + " 이 끈적이는 촉수를 휘두릅니다.", 5);
        int damage = getAttackPower() - player->getDefence();
        if (damage < 1) damage = 1;

        return damage;
    }

    int SpecialAttack(Player* player) override {
        int initialdamage = getAttackPower() * 1.5; //부식액으로 살짝 더 강한 피해
        int armorreduction = 3; //깎아낼 플레이어 방어력 수치
        int damage = 0;

        LogManager::TypePrint(getName() + " 이(가) 몸을 부풀리더니 강산성 점액을 사방으로 뿜어냅니다.", 5);

        if (player != nullptr) {
            int currentarmor = player->getDefence();
            player->setDefence(currentarmor - armorreduction);

            damage = initialdamage - player->getDefence();
            if (damage < 1) damage = 1;

            LogManager::TypePrint("\n강한 산성에 의해 플레이어의 보호구가 녹아내려 방어력이 " + std::to_string(armorreduction) + " 감소합니다.", 5);
        }
        return damage;
    }
};
