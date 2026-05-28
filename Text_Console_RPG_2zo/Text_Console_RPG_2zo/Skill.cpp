#include <iostream>
#include <iomanip>
#include <cstdlib>

#include "Skill.h"
#include "Player.h"
#include "Monster.h"
#include "BattleSystem.h"   // DamageCalculate 사용

using namespace std;

void TakeDamage(Monster* monster, int damage)
{
    monster->setHp(monster->getHp() - damage);
}

void TakeDamage(Player* player, int damage)
{
    player->setHp(player->getHp() - damage);
}


// ── 흑마법사 : 지옥불길 
// SAN 10 소모. 데미지 = power * (1 + 0.1 * level) - 몬스터 방어력
void Skill_Hellfire(Player* player, Monster* monster)
{
    if (player->getSan() < 10)
    {
        cout << "정신력이 부족해 기술을 사용할 수 없다.\n";
        return;
    }

    player->setSan(player->getSan() - 10);

    int damage = static_cast<int>(player->getPower() * (1.0 + 0.1 * player->getLevel()))
        - monster->getDefence();
    if (damage < 1) damage = 1;

    TakeDamage(monster, damage);
    cout << "지옥불길!\n";
    cout << "→ " << monster->getName() << "에게 " << damage << "의 피해!\n";
}

// ── 흑마법사 : 정신 과부화 
// SAN 15 소모. 데미지만큼 HP 흡수
// 흡수량 = damage * (0.1 * level)
void Skill_MindOverload(Player* player, Monster* monster)
{
    if (player->getSan() < 15)
    {
        cout << "정신력이 부족해 기술을 사용할 수 없다.\n";
        return;
    }

    player->setSan(player->getSan() - 15);

    int damage = player->getPower() - monster->getDefence();
    if (damage < 1) damage = 1;

    int heal = static_cast<int>(damage * (0.1 * player->getLevel()));

    TakeDamage(monster, damage);
    player->setHp(player->getHp() + heal);

    cout << "정신 과부화!\n";
    cout << "→ " << monster->getName() << "에게 " << damage << "의 피해!\n";
    cout << "→ " << heal << "의 HP를 흡수했다!\n";
}


// ── 파계승 : 심안/무아일격 
// SAN 10 회복 후 기본 공격 1회. 쿨타임 있음
void Skill_MindStrike(Player* player, Monster* monster, int& turn_cycle)
{
    player->setSan(player->getSan() + 10);
    cout << "심안! 정신을 집중하며 공격을 가한다.\n";

    player->Attack(monster);

    int damage = DamageCalculate(player->getPower(), monster->getDefence());
    TakeDamage(monster, damage);
    cout << "→ " << monster->getName() << "에게 " << damage << "의 피해!\n";
    
}


// ── 도적 : 안개 걸음
// 1턴 무적. 쿨타임 있음
void Skill_MistWalk(Player* player, int& turn_cycle)
{
    cout << "안개 걸음! 몸을 안개 속에 숨겨 적의 공격을 흘린다.\n";
}

// ── 도박꾼 : 러시안 룰렛
// 최대 6번 선택. 나한테 쏘면 데미지 중첩(×1.2), 현재 HP 비례 자해 데미지
// 적한테 쏘면 총알 나가든 안 나가든 턴 종료
void Skill_RussianRoulette(Player* player, Monster* monster)
{
    cout << "러시안 룰렛! 리볼버를 집어 들었다...\n";

    float multiplier = 1.0f;
    int remainingChambers = 6;

    for (int shot = 0; shot < 6; shot++)
    {
        cout << "\n현재 배율 : " << fixed << setprecision(1) << multiplier << "배  |  확률 : 1/" << remainingChambers << defaultfloat << "\n";
        cout << "1. 나에게 방아쇠를 당긴다.\n";
        cout << "2. 적에게 방아쇠를 당긴다.\n";
        cout << "선택 : ";

        int choice;
        cin >> choice;

        bool isBullet = (rand() % remainingChambers == 0); // 1/remainingChambers 확률

        if (choice == 1) // 나에게
        {
            if (isBullet)
            {
                int selfDamage = player->getHp() / 2;
                TakeDamage(player, selfDamage);
                cout << "탕! 총알이 발사되었다! " << selfDamage << "의 자해 피해!\n";
                return;
            }
            else
            {
                remainingChambers--;   // 약실 하나 소진 → 확률 상승
                multiplier += 1.2f;
                cout << "딸깍... 공탄이다. 배율이 " << fixed << setprecision(1) << multiplier << defaultfloat << "배로 올랐다.\n";
            }
        }
        else if (choice == 2) // 적에게
        {
            if (isBullet)
            {
                int damage = static_cast<int>(
                    DamageCalculate(player->getPower(), monster->getDefence()) * multiplier);
                TakeDamage(monster, damage);
                cout << "탕! " << monster->getName() << "에게 " << damage << "의 피해!\n";
            }
            else
            {
                cout << "딸깍... 공탄이다. 기회를 놓쳤다.\n";
            }
            return;
        }
        else
        {
            cout << "올바른 행동이 아니다.\n";
            shot--;
        }
    }

    cout << "탄창이 비었다.\n";
}


// ================================================================
// 패시브 — 플레이어가 공격할 때 자동 적용
// BattleSystem의 플레이어 공격 처리 부분에서 호출
// ================================================================
int Skill_PassiveOnAttack(SkillID id, Player* player, int damage)
{
    switch (id)
    {
        // 도박꾼 — 승부사 : 항상 0.7 ~ 1.5배 랜덤 피해
    case SkillID::GAMBLER:
    {
        // 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5 중 하나
        float multiplier = 0.7f + (rand() % 9) * 0.1f;
        return static_cast<int>(damage * multiplier);
    }

    default:
        return damage; // 해당 없는 패시브는 데미지 그대로
    }
}

// ================================================================
// 패시브 — 플레이어가 피해 받을 때 자동 적용
// BattleSystem의 몬스터 공격 처리 부분에서 호출
// ================================================================
int Skill_PassiveOnHit(SkillID id, Player* player, Monster* monster, int damage)
{
    switch (id)
    {
        // 버서커 — 아드레날린 분비 : HP 50% 이하 시 받는 피해 절반
    case SkillID::ADRENALINE:
        if (player->getHp() <= player->getMaxHp() * 0.5)
        {
            cout << "아드레날린 분비! 받는 피해가 절반으로 감소했다.\n";
            return damage / 2;
        }
        return damage;

        // 파계승 — 명경지수 : SAN 90 이상 시 방어력 1.5배로 재계산
    case SkillID::CLEAR_MIND:
        if (player->getSan() > 90)
        {
            int newDamage = monster->getAttackPower() - static_cast<int>(player->getDefence() * 1.5);
            if (newDamage < 1) newDamage = 1;
            cout << "명경지수! 고요한 정신으로 피해를 흘려냈다.\n";
            return newDamage;
        }
        return damage;

    default:
        return damage; // 해당 없는 패시브는 데미지 그대로
    }
}

