#include "Poor.h"
#include "Monster.h"
#include <iostream>

using namespace std;

Poor::Poor(string name, string job)
    : Player(name, job)
{
}

void Poor::Attack(Monster* monster)
{
    if (monster == nullptr) return;

    cout << "당신은 손을 벌벌 떨며.. " << monster->getName()
         << "에게 낡고 허름한 몽둥이를 휘두릅니다!" << endl;

    monster->TakeDamage(this->getPower() - monster->getDefence);

    SkillData Poor::getSkillData(int skillIndex)
    {
        if (skillIndex == 1)
            return
        {
            SkillID::SHABBY, "남루한 행색",
            "당신은 가진 것이 아무것도 없습니다.\n"
            "오직 실력으로만 살아남으십시오."
            , true, 0
        };
        else
            return
        {
            SkillID::FRAIL_BODY, "비루한 몸뚱아리",
            "평생을 굶주림과 영양실조에 시달렸습니다.\n"
            "레벨업 시, [능력치 증가]폭이 소폭 감소합니다."
            , true, 0
        };
    }
    void Poor::useSkill(int skillIndex, Monster * monster, int& turn_cycle)
}

