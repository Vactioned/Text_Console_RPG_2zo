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

    cout << "당신은 기괴한 주문을 읊조리며, " << monster->getName()
         << "의 생명력을 갉아먹습니다!" << endl;
}

SkillData Warlock::getSkillData(int skillIndex)
{
    if (skillIndex == 1)
    {
        return
        {
            SkillID::HELLFIRE, "지옥불길",
            "[정신력]을 [10]소모하여, 강화된 [일반공격]을 시전합니다.",
            false, 0
        };
    }
      
    else
    {
        return
        {
            SkillID::MIND_OVERLOAD, "정신 과부화",
            "[정신력]을 [15]소모하여, 피해량의 일정 수치만큼 [HP]를 회복합니다.",
            false, 0
        };
    }      
}

void Warlock::useSkill(int skillIndex, Monster* monster, int& turn_cycle)
{
    if (skillIndex == 1) Skill_Hellfire(this, monster);
    else if (skillIndex == 2) Skill_MindOverload(this, monster);
}

