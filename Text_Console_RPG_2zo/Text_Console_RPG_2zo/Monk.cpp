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

    cout << "당신은 짧은 거리에서 뿜어낸 촌경으로, " << monster->getName()
         << "의 복부를 강타합니다!" << endl;

    monster->TakeDamage(this->getPower() - monster->getDefence);

    SkillData Monk::getSkillData(int skillIndex)
    {
        if (skillIndex == 1)
            return { SkillID::CLEAR_MIND, "명경지수", "[정신력] 이 90 이상일 때, [방어력] 1.5배 올라갑니다.", false, 0 };
        else
            return { SkillID::MIND_STRIKE, "심안/무아일격" , "[정신력] 을 n 회복한 뒤, 기본공격 1회를 합니다. (쿨타임 3턴)", false, 3 };
    }
    void Monk::useSkill(int skillIndex, Monster * monster, int& turn_cycle)
}
