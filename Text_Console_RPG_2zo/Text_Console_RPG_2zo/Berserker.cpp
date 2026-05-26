#include "Berserker.h"
#include <iostream>

using namespace std;

Berserker::Berserker(string name, string job)
    : Player(name, job)
{
}

void Berserker::Attack(Monster* monster)
{
    if (monster == nullptr) return;

    cout << "당신은 광기에 찬 함성을 지르며, " << monster->getName()
         << "의 목을 향해 도끼를 내려찍습니다!" << endl;

    monster->TakeDamage(this->getPower());
}

