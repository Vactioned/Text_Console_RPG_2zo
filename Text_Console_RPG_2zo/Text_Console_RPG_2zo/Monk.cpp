#include "Monk.h"
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

    monster->TakeDamage(this->getPower());
}
