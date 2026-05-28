#pragma once
#include "Monster.h"
#include "Player.h"
#include "LogManager.h"
#include <cstdlib>
#include <iostream>

//정신 공격력이 강력한게 포인트

class VoidEcho : public Monster {
public:
    VoidEcho(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 15 + 1) + (playerlevel * 37), // 체력
            rand() % (playerlevel * 5 + 1) + (playerlevel * 6),  // 공격력
            15, // 정신공격력
            5, // 몬스터 방어력
            "[공허의 메아리]") // 몬스터이름

    {

    }

    void Encounter() override {
        std::cout << "\n형체가 없다. 그저 공허한 비명 소리만이 사방에서 울려퍼지더니, [공허의 메아리] 가 서서히 윤곽을 맺는다.\n" << std::endl;
    }

    int NormalAttack(Player* player) override {
        int finalSanDamage = getSanPower() - player->getSanDefence();
        if (finalSanDamage < 1) finalSanDamage = 1;

        player->setSan(player->getSan() - finalSanDamage);

        LogManager::TypePrint(getName() + " 의 비명이 당신의 정신을 관통합니다. 정신력이 " + std::to_string(finalSanDamage) + "만큼 감소합니다.", 5);
        return 0;
    }

    int SpecialAttack(Player* player) override {
        LogManager::TypePrint(getName() + " 이(가) 당신의 내면 깊은 곳의 공포를 실체화하여 쏟아붓습니다.", 5);

        if (player != nullptr) {

            int sandamage = (getSanPower() * 5) - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);
            LogManager::TypePrint("\n끔찍한 공포가 영혼을 짓누릅니다. 정신력이 " + std::to_string(sandamage) + "만큼 감소합니다.", 5);
        }
        return 0;
    }
};

