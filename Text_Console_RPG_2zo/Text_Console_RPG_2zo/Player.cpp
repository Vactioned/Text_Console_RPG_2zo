#include "Player.h"

using namespace std;

Player::Player(std::string name, std::string job)
    : name(name), job(job)
    
{
    maxhp = 200;
    hp = 200;
    maxsan = 100;
    san = 100;
    power = 30;
    defence = 10;
    sandefence = 5;

    level = 1;
    exp = 0;
    maxexp = 100;

    attackBoostAmount = 0;
    attackBoostApplied = false;
}

Player::~Player()
{
}

// getter
string Player::getName() const { return name; }
string Player::getJob() const { return job; }

int Player::getHp() const { return hp; }
int Player::getMaxHp() const { return maxhp; }

int Player::getSan() const { return san; }
int Player::getMaxSan() const { return maxsan; }

int Player::getPower() const { return power; }
int Player::getDefence() const { return defence; }
int Player::getSanDefence() const { return sandefence; }

int Player::getLevel() const { return level; }
int Player::getExp() const { return exp; }
int Player::getMaxExp() const { return maxexp; }

int Player::getAttackBoostAmount() const { return attackBoostAmount; }
bool Player::isAttackBoostApplied() const { return attackBoostApplied; }
    
//setter
void Player::setHp(int HP) { this->hp = HP; }
void Player::setMaxHp(int maxHP) { this->maxhp = maxHP; }

void Player::setSan(int SAN) { this->san = SAN; }
void Player::setMaxSan(int maxSAN) { this->maxsan = maxSAN; }

void Player::setPower(int power) { this->power = power; }
void Player::setDefence(int defence) { this->defence = defence; }
void Player::setSanDefence(int sanDefence) { this->sandefence = sanDefence; }

void Player::setLevel(int level) { this->level = level; }
void Player::setExp(int Exp) { this->exp = Exp; }
void Player::setMaxExp(int maxExp) { this->maxexp = maxExp; }

void Player::setAttackBoostAmount(int amount) { attackBoostAmount = amount; }
void Player::setAttackBoostApplied(bool value) { attackBoostApplied = value; }

// 플레이어 스탯 확인
void Player::PrintPlayerStatus() const
{
    cout << "========================================" << endl;
    cout << "이름: " << name << "| 직업: " << job << "| Lv. " << level << "Exp: " << exp << " / " << maxexp << endl;
    cout << "HP: " << hp << " / " << maxhp << "| 정신력: " << san << " / " << maxsan << endl;
    cout << "공격력: " << power << "| 방어력: " << defence << "| 정신방어력: " << sandefence << endl;
    cout << "========================================" << endl;
}

