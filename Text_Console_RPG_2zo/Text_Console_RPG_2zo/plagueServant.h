#pragma once
#include "Monster.h"
#include "Player.h"
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

    void NormalAttack(Player* player) override {
        std::cout << getName() << "이 오염된 손톱으로 찌르기를 시전합니다!" << std::endl;

        if (player != nullptr) {

            int damage = getAttackPower() - player->getDefence();
            if (damage < 1) damage = 1;

            player->setHp(player->getHp() - damage);
            std::cout << "->" << damage << "의 물리 피해를 입혔습니다!" << std::endl;
        }
    }
    //플레이어에게 방어력은 빼앗아 자신의 방어력을 올리는 특수공격을 실행
    void SpecialAttack(Player* player) override {
        int armorstealamount = 4; //방어력을 뺴앗아올 수치
        int initialdamage = getAttackPower() * 1.3;

        std::cout << getName() << "이 비명을 지르며 역병을 퍼트립니다!" << std::endl;

        if (player != nullptr) {
            int playerarmor = player->getDefence();
            player->setDefence(playerarmor - armorstealamount);

            int myarmor = getDefence();
            setDefence(myarmor + armorstealamount);

            std::cout << "역병이 장비를 부식시키며 플레이어의 방어력이" << armorstealamount << "감소됩니다!" << std::endl;
            std::cout << "부식된 철가루가" << getName() << "의 방어력을" << armorstealamount << "증가시킵니다!" << std::endl;

            int finaldamage = initialdamage = player->getDefence();
            if (finaldamage < 1) finaldamage = 1;

            player->setHp(player->getHp() - finaldamage);
            std::cout << "->" << finaldamage << "의 역병피해를 입혔습니다!" << std::endl;

        }
    }
};
