#include "Berserker.h"
#include "Monster.h"
#include <iostream>

using namespace std;

Berserker::Berserker(string name, string job)
    : Player(name, job)
{
}

void Berserker::Attack(Monster* monster)
{
    if (monster == nullptr) return;

    cout << "당신은 광기에 찬 함성을 지르며, " << monster->getName()
         << "의 목을 향해 도끼를 내려찍습니다!" << endl;

    monster->TakeDamage(this->getPower() - monster->getDefence);

    SkillData Berserker::getSkillData(int skillIndex)
    {
        if (skillIndex == 1)
            return { SkillID::BERSERK, "광폭화", "레벨업을 할 때마다, [공격력] +5 의 추가 스탯을 얻습니다.", true, 0 };
        else
            return { SkillID::ADRENALINE, "아드레날린 분비", "[HP] 가 50% 이하일 때, 피해를 절반만 입습니다.", true, 0 };
    }
    void Berserker::useSkill(int skillIndex, Monster * monster, int& turn_cycle)
}

