#pragma once
#include "Monster.h"
#include "Player.h"
#include "LogManager.h"
#include <cstdlib>
#include <iostream>



class CorruptedKnight : public Monster {
public:
    CorruptedKnight(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 13 + 1) + (playerlevel * 32), // 체력
            rand() % (playerlevel * 5 + 1) + (playerlevel * 5),  // 공격력
            15, // 정신공격력
            5, // 몬스터 방어력
            "[부패한 기사단장]") // 몬스터이름

    {

    }

    void Encounter() override {
        std::cout << "\n무겁게 철컥이는 갑옷 소리가 울려퍼진다. 한때 영주를 지키던 [부패한 기사단장] 의 눈에는 기괴한 색의 광기만이 남아있다.\n" << std::endl;
    }

    int NormalAttack(Player* player) override {
        LogManager::TypePrint(getName() + " 이(가) 보랏빛으로 물든 검을 휘둘러 공간을 일그러트리는 참격을 가합니다.", 5);
        int physdamage = 0;

        if (player != nullptr) {

            physdamage = (getAttackPower() *2) - player->getDefence();
            if (physdamage < 1) physdamage = 1;

        }
        return physdamage;
    }

    int SpecialAttack(Player* player) override {
        LogManager::TypePrint(getName() + " 이(가) 눈을 번득이며 공허의 기운을 담아 횡으로 대검을 휘두릅니다.", 5);


        int physdamage = 0;

        if (player != nullptr) {

            physdamage = (getAttackPower() * 3) - player->getDefence();
            if (physdamage < 1) physdamage = 1;

            int sandamage = (getSanPower()*2) - player->getSanDefence();
            if (sandamage < 1) sandamage = 1;

            player->setSan(player->getSan() - sandamage);

            LogManager::TypePrint("\n검 끝에서 뿜어져 나오는 공허가 영혼을 갉아먹습니다. 정신력이 " + std::to_string(sandamage) + "만큼 감소합니다.", 5);
        }
        return physdamage;
    }
};
