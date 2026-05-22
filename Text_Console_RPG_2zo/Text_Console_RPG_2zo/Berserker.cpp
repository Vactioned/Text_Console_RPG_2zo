#include "Berserker.h"
#include "Monster.h"
#include <iostream>

using namespace std;

Berserker::Berserker(string name, string job)
    : Player(name, job)
{
}
    void Berserker::attack(Monster * monster)
    {
        cout << monster->Getname() << "에게 도끼를 휘두릅니다!" << endl;
    }
    
