#include "Thief.h"
#include "Monster.h"
#include <iostream>

using namespace std;

Thief::Thief(string name, string job)
    : Player(name, job)
{
}

void Thief::Attack(Monster* monster)
{
    if (monster == nullptr) return;

    cout << "당신은 어둠 속에 숨어들어, " << monster->getName()
         << "의 사각지대에서 단검을 기습적으로 찔러넣습니다!" << endl;

    monster->TakeDamage(this->getPower() - monster->getDefence);

    SkillData Thief::getSkillData(int skillIndex)
    {
        if (skillIndex == 1)
            return { SkillID::PLUNDER, "약탈", "[아이템 드랍률] 확률이 2배 증가합니다.", true, 0 };
        else
            return { SkillID::MIST_WALK, "안개 걸음", "1턴 동안 [무적] 상태가 되며, 공격을 받으면 반격합니다. (쿨타임 3턴)" false, 3 };
    }
    void Thief::useSkill(int skillIndex, Monster* monster, int& turn_cycle)
}    
