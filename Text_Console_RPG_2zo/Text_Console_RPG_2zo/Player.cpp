#include "Player.h"

using namespace std;

Player::Player(std::string name, std::string job)
    : name(name), job(job)
    
{
    maxHP = 200;
    HP = 200;
    maxSAN = 100;
    SAN = 100;
    power = 30;
    defence = 10;

    level = 1;
    Exp = 0;
    maxExp = 100;
}

Player::~Player()
{
}

string Player::getName() const { return name; }
string Player::getJob() const { return job; }

int Player::getHP() const { return HP; }
int Player::getmaxHP() const { return maxHP; }
int Player::getSAN() const { return SAN; }
int Player::getmaxSAN() const { return maxSAN; }

int Player::getPower() const { return power; }
int Player::getDefence() const { return defence; }

int Player::getLevel() const { return level; }
int Player::getExp() const { return Exp; }
int Player::getmaxExp() const { return maxExp; }

void Player::setHP(int HP)
{
    this->HP = HP;
}
void Player::setmaxHP(int maxHP)
{
    this->maxHP = maxHP;
}
void Player::setSAN(int SAN)
{
    this->SAN = SAN;
}
void Player::setmaxSAN(int maxSAN)
{
    this->maxSAN = maxSAN;
}
void Player::setPower(int power)
{
    this->power = power;
}
void Player::setDefence(int defence)
{
    this->defence = defence;
}
void Player::setLevel(int level)
{
    this->level = level;
}
void Player::setExp(int Exp)
{
    this->Exp = Exp;
}
void Player::setmaxExp(int maxExp)
{
    this->maxExp = maxExp;
}

