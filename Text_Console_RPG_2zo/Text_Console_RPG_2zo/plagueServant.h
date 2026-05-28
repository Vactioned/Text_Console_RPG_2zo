#pragma once
#include "Monster.h"
#include "Player.h"
#include "LogManager.h"
#include <cstdlib>
#include <iostream>



class PlagueServant : public Monster {
public:
    PlagueServant(int playerlevel)
        :Monster(rand() % (playerlevel * 10 + 1) + (playerlevel * 20), // 체력
            rand() % (playerlevel * 5 + 1) + (playerlevel * 5),  // 공격력
            5, // 정신공격력
            5, // 몬스터 방어력
            "[역병의 하수인]") // 몬스터이름

    {

    }

    void Encounter() override {
        std::cout << "\n썩어가는 살점이 눈에 들어온다. [역병의 하수인] 이(가) 온몸에 돋아난 붉은 발진과 종기를 드러내며 비틀거리고 나타난다.\n" << std::endl;
    }

    int NormalAttack(Player* player) override {
        LogManager::TypePrint(getName() + " 이 고름이 낀 손톱을 휘두릅니다.", 5);
        int damage = getAttackPower() - player->getDefence();
        if (damage < 1) damage = 1;

        return damage;
    }

    //플레이어에게 방어력은 빼앗아 자신의 방어력을 올리는 특수공격을 실행
    int SpecialAttack(Player* player) override {
        int armorstealamount = 4; //방어력을 뺴앗아올 수치
        int initialdamage = getAttackPower() * 1.5;
        int finaldamage = 0;

        LogManager::TypePrint(getName() + " 이 비명을 지르며 역병을 퍼트립니다.", 5);

        if (player != nullptr) {
            int playerarmor = player->getDefence();
            player->setDefence(playerarmor - armorstealamount);

            int myarmor = getDefence();
            setDefence(myarmor + armorstealamount);

            LogManager::TypePrint("\n역병이 장비를 부식시켜 방어력이 " + std::to_string(armorstealamount) + "만큼 감소합니다.", 5);

            int finaldamage = initialdamage - player->getDefence();
            if (finaldamage < 1) finaldamage = 1;

            LogManager::TypePrint("\n떨어져 나온 철가루가 " + getName() + " 에게 달라붙어 방어력이 " + std::to_string(armorstealamount) + " 증가합니다.", 5);
        }
        return finaldamage;
    }
};
