#include "Warlock.h"
#include "Monster.h"
#include <iostream>

using namespace std;

Warlock::Warlock(string name, string job)
    : Player(name, job)
{
}

void Warlock::Attack(Monster* monster)
{
    if (monster == nullptr) return;

    cout << "당신은 지팡이를 치켜들며, " << monster->getName()
         << "의 생명력을 갉아먹습니다!" << endl;

    monster->TakeDamage(this->getPower() - monster->getDefence);

    SkillData Warlock::getSkillData(int skillIndex)
    {
        if (skillIndex == 1)
            return { SkillID::HELLFIRE, "지옥불길", "[정신력] 을 10 소모한 뒤, 강화된 공격을 사용합니다.", false, 0 };
        else
            return { SkillID::MIND_OVERLOAD, "정신 과부화", "[정신력] 을 15 소모한 뒤, 일정 피해만큼 [HP] 를 회복합니다." false, 0 };
    }   
    void Warlock::useSkill(int skillIndex, Monster * monster, int& turn_cycle)
}
