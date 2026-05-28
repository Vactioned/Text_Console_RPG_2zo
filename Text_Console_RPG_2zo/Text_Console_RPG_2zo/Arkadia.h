#pragma once
#include "Monster.h"
#include "Player.h"
#include "LogManager.h"
#include <cstdlib>
#include <iostream>



class Arkadia : public Monster {

private:
    bool isCharging; //차징 상태 확인용

public:
    Arkadia(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 15 + 1) + (playerlevel * 40), // 체력
            rand() % (playerlevel * 5 + 1) + (playerlevel * 5),  // 공격력
            20, // 정신공격력
            5, // 몬스터 방어력
            "[도달자, 아르카디아]"), // 몬스터이름
            isCharging(false)


    {

    }

    void Encounter() override {
        std::cout << "\n넘어왔다. 넘어올 수 없는 경계를 밟고. 차원과 차원 사이를 맨손으로 찢어발기고 이쪽 세계에 발을 디딘 것. [도달자, 아르카디아] 가 검은 에너지를 손끝에 천천히 감으며 공허가 담긴 눈으로 당신을 바라본다.\n" << std::endl;
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
            LogManager::TypePrint(getName() + " 이(가) 허공에서 검은 에너지를 응축합니다...", 5);

            return 0;
        }
        else {
            // 2단계 방출
            isCharging = false;
            LogManager::TypePrint(getName() + " 이(가) 검은 에너지를 폭발시킵니다.", 5);

            int physdamage = 0;

            if (player != nullptr) {
                physdamage = (getAttackPower() * 4) - player->getDefence();
                if (physdamage < 1) physdamage = 1;

                int sandamage = (getSanPower() * 3) - player->getSanDefence();
                if (sandamage < 1) sandamage = 1;

                player->setSan(player->getSan() - sandamage);
                LogManager::TypePrint("\n영혼까지 꿰뚫리는 고통. 정신력이 " + std::to_string(sandamage) + " 감소합니다.", 5);
            }
            return physdamage;
        }

    }
};

