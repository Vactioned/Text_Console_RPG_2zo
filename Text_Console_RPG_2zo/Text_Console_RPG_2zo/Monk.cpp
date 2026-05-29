#include "Monk.h"
#include "Monster.h"
#include <iostream>

using namespace std;

Monk::Monk(string name, string job)
    : Player(name, job)
{
}

void Monk::Attack(Monster* monster)
{
    if (monster == nullptr) return;
    cout << "================================================================" << endl;
    cout << "당신은 숨을 깊게 들이 마신 뒤, " << monster->getName()
         << "에게 짧은 거리에서 뿜어낸 촌경으로 강타합니다!" << endl;
}

SkillData Monk::getSkillData(int skillIndex)
{
    if (skillIndex == 1)
    {
        return
        {
            SkillID::CLEAR_MIND, "명경지수",
            "[정신력]이 [90]이상일 때, [방어력]이 [50%]증가합니다",
            true, 0
        };
    }
    else
    {
        return
        {
            SkillID::MIND_STRIKE, "심안/무아일격",
            "[정신력]을 [n]회복한 후, [일반공격][1회]를 가합니다. [재사용 대기시간: 3턴]",
            false, 3
        };
    }
}

void Monk::useSkill(int skillIndex, Monster* monster, int& turn_cycle)
{
    if (skillIndex == 2) Skill_MindStrike(this, monster, turn_cycle);
}
