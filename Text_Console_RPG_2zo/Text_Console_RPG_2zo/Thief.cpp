#include "Thief.h"
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

    monster->TakeDamage(this->getPower());
}
