#pragma once
#include "Monster.h"
#include "Player.h"
#include "LogManager.h"
#include <cstdlib>
#include <iostream>

class CorpseGolem : public Monster {
private:
    int attackcount;
public:
    CorpseGolem(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 20 + 1) + (playerlevel * 30), // 체력
            rand() % (playerlevel * 8 + 1) + (playerlevel * 10),  // 공격력
            0, // 정신공격력
            18, // 몬스터 방어력
            "[시체골렘]"), // 몬스터이름
            attackcount(0)

    {

    }

    void Encounter() override {
        std::cout << "\n부패한 살의 냄새가 압도적으로 밀려온다. 셀 수 없는 시체가 하나로 뭉쳐진 거체가 눈앞을 가로막으며, [시체골렘] 이(가) 천천히 당신을 향해 돌아선다.\n" << std::endl;
    }

    int NormalAttack(Player* player) override {
        attackcount++;
        int bonusdamage = attackcount * 3; //공격할때마다 3의 추가 데미지 누적
        int finaldamage = getAttackPower() + bonusdamage;
        int actualdamage = 0;

        LogManager::TypePrint(getName() + " 이 시체로 뭉친 거대한 주먹을 휘두릅니다.", 5);

        setAttackPower(getAttackPower() + 2);
        LogManager::TypePrint("\n" + getName() + " 의 공격력이 2만큼 영구히 상승합니다. [" + std::to_string(attackcount) + "회 누적]", 5);

        if (player != nullptr) {
            actualdamage = finaldamage - player->getDefence();
            if (actualdamage < 1) actualdamage = 1;
        }
        return actualdamage;
    }

    int SpecialAttack(Player* player) override {
        int ultdamage = getAttackPower() * 1.3; //특수공격 데미지 배율
        int armorreduction = 6; //감소시킬 방어력 수치

        LogManager::TypePrint(getName() + " 이 대지를 후려쳐 균형을 잃게 만듭니다.", 5);

        if (player != nullptr) {
            int currentarmor = player->getDefence();
            player->setDefence(currentarmor - armorreduction);
            LogManager::TypePrint("\n충격으로 방어력이 " + std::to_string(armorreduction) + "만큼 감소합니다.", 5);

            int actualultdamage = ultdamage - player->getDefence();
            if (actualultdamage < 1) actualultdamage = 1;

            LogManager::TypePrint("\n" + getName() + " 이 시체로 뭉친 주먹으로 빈틈을 놓치지 않고 후속타를 날립니다.", 5);

            int followdamage = NormalAttack(player);
            player->setHp(player->getHp() - followdamage);  // 트루데미지

            return actualultdamage;
        }
        return 0;
    }
};
