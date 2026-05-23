#include "Berserker.h"
#include "Monster.h"
#include <iostream>

using namespace std;

Berserker::Berserker(string name, string job)
    : Player(name, job)
{
}
    void Berserker::Attack(Monster * monster)
    {
    // gatname 소문자로 수정되면 마저 작성할 것.
        cout << monster->getname() << "에게 도끼를 휘두릅니다!" << endl;
    }
    
