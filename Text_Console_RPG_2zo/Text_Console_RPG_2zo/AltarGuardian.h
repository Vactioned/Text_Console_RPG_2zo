#pragma once
#include "Monster.h"
#include "Player.h"
#include "LogManager.h"
#include <cstdlib>
#include <iostream>



class AltarGuardian : public Monster {
public:
    AltarGuardian(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 15 + 1) + (playerlevel * 37), // 체력
            rand() % (playerlevel * 4 + 1) + (playerlevel * 6),  // 공격력
            0, // 정신공격력
            5, // 몬스터 방어력
            "[제단의 파수병]") // 몬스터이름

    {

    }

    void Encounter() override {
        std::cout << "\n제단 앞을 막아선 거대한 그림자. [제단의 파수병] 이(가) 육중한 몸을 돌리며 침입자를 향해 천천히 발을 내딛는다.\n" << std::endl;
    }

    int NormalAttack(Player* player) override {
        LogManager::TypePrint(getName() + " 이(가) 육중한 발로 당신을 짓밟습니다.", 5);
        int physdamage = 0;

        if (player != nullptr) {

            physdamage = getAttackPower() - player->getDefence();
            if (physdamage < 1) physdamage = 1;
        }
        return physdamage;
    }

    int SpecialAttack(Player* player) override {

        LogManager::TypePrint(getName() + " 이(가) 분노하며 주먹으로 땅을 내려칩니다.", 5);
        int physdamage = 0;

        if (player != nullptr) {

            LogManager::TypePrint("\n충격으로 인해 방어 장비가 파손되어 방어력이 5 감소합니다.", 5);
            player->setDefence(player->getDefence() - 5);

            physdamage = (getAttackPower() * 2.5) - player->getDefence();
            if (physdamage < 1) physdamage = 1;
        }
        return physdamage;
    }
};

