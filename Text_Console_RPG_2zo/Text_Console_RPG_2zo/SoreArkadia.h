#pragma once
#include "Monster.h"
#include "Player.h"
#include "LogManager.h"
#include <cstdlib>
#include <iostream>



class SoreArkadia : public Monster {

private:
    bool isCharging; //차징 상태 확인용

public:
    SoreArkadia(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 15 + 1) + (playerlevel * 37), // 체력
            rand() % (playerlevel * 4 + 1) + (playerlevel * 6),  // 공격력
            20, // 정신공격력
            5, // 몬스터 방어력
            "[부상당한 아르카디아]"), // 몬스터이름
        isCharging(false)


    {

    }

    void Encounter() override {
        std::cout << "\n온몸의 상처가 가득한 [부상당한 아르카디아] 의 숨소리가 거칠다. 그럼에도 네크로노미콘을 놓지 않는다. 저것이 저 자의 손에 남아있는 한, 이 제단 앞에서 무슨 일이 벌어질지 알 수 없다. [부상당한 아르카디아] 가 피를 흘리면서도 당신 앞을 막아선다.\n" << std::endl;
    }

    int NormalAttack(Player* player) override {

        if (isCharging) {       // 차징 중에는 특수공격으로 넘어감
            return SpecialAttack(player);
        }

        LogManager::TypePrint(getName() + " 이(가) 차원의 틈을 찢으며 일격을 가합니다.", 5);

        int physdamage = 0;

        if (player != nullptr) {

            physdamage = getAttackPower() - player->getDefence();
            if (physdamage < 1) physdamage = 1;

            int sandamage = (getSanPower() / 2) - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);
            LogManager::TypePrint("\n찢어진 차원의 틈으로 공허를 마주합니다. 정신력이 " + std::to_string(sandamage) + " 감소합니다.", 5);
        }
        return physdamage;
    }

    int SpecialAttack(Player* player) override {
        if (!isCharging) {
            // 1단계 차징 준비
            isCharging = true;
            LogManager::TypePrint(getName() + " 이(가) 떨리는 손으로 검은 에너지를 억지로 끌어모읍니다...", 5);

            return 0;
        }
        else {
            // 2단계 방출
            isCharging = false;
            LogManager::TypePrint(getName() + " 이(가) 불완전하게 응축된 에너지를 억지로 방출합니다.", 5);

            int physdamage = 0;

            if (player != nullptr) {
                physdamage = (getAttackPower() * 2.5) - player->getDefence();
                if (physdamage < 1) physdamage = 1;

                int sandamage = getSanPower() - player->getSanDefence();
                if (sandamage < 1) sandamage = 1;

                player->setSan(player->getSan() - sandamage);
                LogManager::TypePrint("\n제어되지 못한 공허가 흘러넘칩니다. 정신력이 " + std::to_string(sandamage) + "만큼 감소합니다.", 5);
            }
            return physdamage;
        }

    }
};

