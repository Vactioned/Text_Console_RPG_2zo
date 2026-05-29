#pragma once
#include "Monster.h"
#include "Player.h"
#include "LogManager.h"
#include <cstdlib>
#include <iostream>




class VoidHound : public Monster {
public:
    VoidHound(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 10 + 1) + (playerlevel * 20), // 체력
            rand() % (playerlevel * 5 + 1) + (playerlevel * 5),  // 공격력
            0, // 정신공격력
            5, // 몬스터 방어력
            "[공허의 파수견]") // 몬스터이름

    {

    }

    void Encounter() override {
        std::cout << "\n어둠 속에서 낮은 숨소리가 들려온다. [공허의 파수견] 이(가) 붉은 눈을 빛내며 천천히 모습을 드러낸다.\n" << std::endl;
    }

    int NormalAttack(Player* player) override {
        LogManager::TypePrint(getName() + " 이 날카로운 이빨로 물어뜯습니다.", 5);
        int damage = getAttackPower() - player->getDefence();

        if (player != nullptr) {
            if (damage < 1) damage = 1;
        }
        return damage;
    }

    int SpecialAttack(Player* player) override {
        int initialdamage = getAttackPower()* 1.5; // 즉시 들어가는 타격 피해
        int buffamount = 4;                // 증가할 공격력수치
        int damage = initialdamage - player->getDefence();
        if (damage < 1) damage = 1;

        LogManager::TypePrint(getName() + " 이 붉은 눈을 드러내며 이빨을 피부 깊숙하게 쑤셔 넣습니다.", 5);

        setAttackPower(getAttackPower() + buffamount);
        LogManager::TypePrint("\n" + getName() + " 의 이빨이 공허 에너지로 강화되어 공격력이 영구히 " + std::to_string(buffamount) + "만큼 증가합니다.", 5);

        return damage;
    }
};
