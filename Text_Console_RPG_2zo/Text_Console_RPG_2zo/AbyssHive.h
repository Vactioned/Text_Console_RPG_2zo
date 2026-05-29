#pragma once
#include "Monster.h"
#include "Player.h"
#include "LogManager.h"
#include <cstdlib>
#include <iostream>



class AbyssHive : public Monster {
public:
    AbyssHive(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 10 + 1) + (playerlevel * 24), // 체력
            0,  // 공격력
            10, // 정신공격력
            5, // 몬스터 방어력
            "[심연의 군체]") // 몬스터이름

    {

    }

    void Encounter() override {
        std::cout << "\n공간이 좁아지는 느낌이 든다. [심연의 군체] 가 끝없이 뻗어나오는 촉수로 사방의 퇴로를 막기 시작한다.\n" << std::endl;
    }

    int NormalAttack(Player* player) override {
        LogManager::TypePrint(getName() + " 의 몸체에서 수십 개의 형체 없는 촉수가 나와 당신을 무자비하게 내려칩니다.", 5);

        if (player != nullptr) {
            int sandamage = getSanPower() - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);
            LogManager::TypePrint("\n촉수의 영체가 당신의 영혼에 피해를 입힙니다. 정신력이 " + std::to_string(sandamage) + "만큼 감소합니다.", 5);
        }
        return 0;
    }

    int SpecialAttack(Player* player) override {
        int defenceReduction = 5; // 깎아낼 플레이어의 정신 방어력 수치
        LogManager::TypePrint(getName() + " 이(가) 거대한 가시 촉수로 사지를 포박하고 머리속을 헤집습니다.", 5);

        if (player != nullptr) {
            //특수능력 플레이어의 정신방어력을 깎아내림
            int currentSanDef = player->getSanDefence();
            player->setSanDefence(currentSanDef - defenceReduction);

            //정신 방어력이 깎인 상태를 실시간 반영
            int finaldamage = (getSanPower() * 1.5) - player->getSanDefence();
            if (finaldamage < 1) finaldamage = 1;

            //정신력을 직접 차감
            player->setSan(player->getSan() - finaldamage);
            LogManager::TypePrint("\n촉수가 머리를 파고들어 정신 방어력이 " + std::to_string(defenceReduction) + "만큼 감소하며, 정신력이 " + std::to_string(finaldamage) + "만큼 감소합니다.", 5);
        }
        return 0;
    }
};
