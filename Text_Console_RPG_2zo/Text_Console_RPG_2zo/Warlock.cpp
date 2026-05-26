#include "Warlock.h"
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

    monster->TakeDamage(this->getPower());
}
