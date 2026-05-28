#pragma once
#include "Monster.h"
#include "Player.h"
#include <cstdlib>
#include <iostream>

class CorpseGolem : public Monster {
private:
    int attackcount;
public:
    CorpseGolem(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 20 + 1) + (playerlevel * 30), // 체력
            rand() % (playerlevel * 8 + 1) + (playerlevel * 10),  // 공격력
            0, // 정신공격력
            18, // 몬스터 방어력
            "보스[시체골렘]"), // 몬스터이름
            attackcount(0)

    {
        
    }

    void Encounter() override {
        std::cout << "\n(출력대사) " << getName() << "이(가) 앞을 가로막습니다!\n" << std::endl;
    }

    int NormalAttack(Player* player) override {
        attackcount++;
        int bonusdamage = attackcount * 3; //공격할때마다 3의 추가 데미지 누적
        int finaldamage = getAttackPower() + bonusdamage;
        int actualdamage = 0;

        std::cout << getName() << " 시체로 뭉친 거대한 주먹을 휘두릅니다![스택: " << attackcount << "회째]" << std::endl;
        

        setAttackPower(getAttackPower() + 2);
        std::cout << getName() << "의 공격력이 영구히 2 상승합니다!" << std::endl;

        if (player != nullptr) {
            actualdamage = finaldamage - player->getDefence();
            if (actualdamage < 1) actualdamage = 1;

            
            std::cout << "->" << actualdamage << "의 물리 피해를 입혔습니다!" << std::endl;

        }
        return actualdamage;
    }

    int SpecialAttack(Player* player) override {
        int ultdamage = getAttackPower() * 1.3; //특수공격 데미지 배율
        int armorreduction = 6; //감소시킬 방어력 수치
        int totaldamage = 0;

        std::cout << getName() << "이 대지를 후려쳐 플레이어의 균형을 잃게 만듭니다!" << std::endl;


        if (player != nullptr) {
            int currentarmor = player->getDefence();
            player->setDefence(currentarmor - armorreduction);
            std::cout << "충격으로 플레이어의 방어력이" << armorreduction << "감소합니다!" << std::endl;

            int actualultdamage = ultdamage - player->getDefence();
            if (actualultdamage < 1) actualultdamage = 1;

            std::cout << "->" << actualultdamage << "의 파괴적인 물리 피해!!" << std::endl;

            totaldamage += actualultdamage;

            std::cout << getName() << "시체로 뭉친 주먹이 빈틈을 놓치지않고 후속타를 날립니다!" << std::endl;

            int followdamage = NormalAttack(player);
            totaldamage += followdamage;
        }
        return totaldamage;
    }
};
