#include "Gambler.h"
#include "Monster.h"
#include <iostream>

using namespace std;

Gambler::Gambler(string name, string job)
    : Player(name, job)
{
}

void Gambler::Attack(Monster* monster)
{
    if (monster == nullptr) return;

    cout << "당신은 공격할 때마저 도박을 합니다. " << monster->getName()
         << "에게 주사위를 던지며 목숨을 건 베팅을 시작합니다!" << endl;
}

SkillData Gambler::getSkillData(int skillIndex)
{
    if (skillIndex == 1)
    {
        return
        {
            SkillID::GAMBLER, "승부사",
            "[일반공격]시, 항상 무작위 피해를 입힙니다."
            , true, 0
        };
    }
    else
    {
        return
        {
            SkillID::RUSSIAN_ROULETTE, "러시안 룰렛",
            "[실탄 1발]이 장전된 리볼버로 목숨을 건 도박을 시작합니다.\n"
            "[자신]에게 방아쇠를 당길수록 강해지고, [상대]를 쏘면 큰 피해를 입힐 수 있습니다.\n"
            "※ 스스로에게 쏘지 않도록 조심하십시오. ※"
            , false, 0
        };
    }
}

void Gambler::useSkill(int skillIndex, Monster* monster, int& turn_cycle)
{
    if (skillIndex == 2) Skill_RussianRoulette(this, monster);
}
