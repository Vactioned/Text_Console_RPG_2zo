#pragma once
#include "Monster.h"
#include "Player.h"
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

    int NormalAttack(Player* player) override {
        std::cout << getName() << "이 날카로운 이빨로 물어뜯습니다!" << std::endl;
        int damage = getAttackPower() - player->getDefence();

        if (player != nullptr) {
            
            if (damage < 1) damage = 1; //최소데미지 보장

            
            std::cout << "->" << damage << "의 물리 피해를 입혔습니다!" << std::endl;
        }
        return damage;
    }

    int SpecialAttack(Player* player) override {
        int initialdamage = getAttackPower()* 1.5; // 즉시 들어가는 타격 피해
        int buffamount = 4;                // 증가할 공격력수치
        int damage = initialdamage - player->getDefence();
        if (damage < 1) damage = 1;

        std::cout << getName() << "이 붉은 눈을 드러내며 깊숙이 상처를 냅니다![잔혹한 할퀴기]" << std::endl;;

        setAttackPower(getAttackPower() + buffamount);
        std::cout << getName() << "의 이빨이 공허 에너지로 강화되어 공격력이" << buffamount << "영구 증가합니다!" << std::endl;

        
       

        if (player != nullptr) {
           
            std::cout << "->" << damage << "의 물리 피해를 입혔습니다!" << std::endl;
        }
        return damage;
    }
};

