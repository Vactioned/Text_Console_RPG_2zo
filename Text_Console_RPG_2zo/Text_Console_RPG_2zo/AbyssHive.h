#pragma once
#include "Monster.h"
#include "Player.h"
#include <cstdlib>
#include <iostream>



class AbyssHive : public Monster {
public:
    AbyssHive(int playerlevel) //코드 간략화
        :Monster(rand() % (playerlevel * 10 + 1) + (playerlevel * 20), // 체력
            0,  // 공격력
            5, // 정신공격력
            5, // 몬스터 방어력
            "[심연의 군체]") // 몬스터이름

    {
        
    }

    void Encounter() override {
        std::cout << "\n(출력대사) " << getName() << "이(가) 앞을 가로막습니다!\n" << std::endl;
    }

    int NormalAttack(Player* player) override {
        std::cout << getName() << "의 몸체에서 수십 개의 보라색 촉수가 뿜어져 나와 사방을 후려칩니다!" << std::endl;

        if (player != nullptr) {
            int sandamage = getSanPower() - player->getSanDefence();
            if (sandamage < 1) sandamage = 1; 

            player->setSan(player->getSan() - sandamage);
            std::cout << "-> 사방을 조여오는 촉수의 공포가 정신을 " << sandamage << "만큼 붕괴시킵니다!" << std::endl;
        }
        return 0;
    }

    int SpecialAttack(Player* player) override {
        int defenceReduction = 5; // 깎아낼 플레이어의 정신 방어력 수치
        std::cout << getName() << "이(가) 거대한 가시 촉수로 플레이어의 사지를 붙잡고 뇌를 직접 조여옵니다! " << std::endl;

        if (player != nullptr) {
            //특수능력 플레이어의 정신방어력을 깎아내림
            int currentSanDef = player->getSanDefence();
            player->setSanDefence(currentSanDef - defenceReduction);
            std::cout << " 촉수가 머리를 파고들며 플레이어의 정신 방어력이 " << defenceReduction << "만큼 감소합니다!" << std::endl;

            //정신 방어력이 깎인 상태를 실시간 반영
            int finaldamage = (getSanPower() * 1.5) - player->getSanDefence();
            if (finaldamage < 1) finaldamage = 1;

            //정신력을 직접 차감
            player->setSan(player->getSan() - finaldamage);
            std::cout << "-> 머리가 깨질 듯한 극심한 오염! 정신력이 " << finaldamage << "만큼 찢겨나갑니다!" << std::endl;
        }
        return 0;
    }
};
