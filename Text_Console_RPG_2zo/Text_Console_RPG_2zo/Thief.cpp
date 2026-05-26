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
         << "의 사각지대에서 단검을 기습적으로 찔러 넣습니다!" << endl;
}

SkillData Thief::getSkillData(int skillIndex)
{
    if (skillIndex == 1)
    {
        {
            SkillID::PLUNDER, "약탈",
                "[아이템 드랍률]확률이 증가합니다.",
                true, 0
        };
    }
    else
    {
        return
        {
            SkillID::MIST_WALK, "안개 걸음",
            "[1턴]동안 [무적]상태가 되며, 피격 시 반격합니다. [재사용 대기시간: 3턴]",
            false, 3
        };
    }        
}

void Thief::useSkill(int skillIndex, Monster* monster, int& turn_cycle)
{
}
