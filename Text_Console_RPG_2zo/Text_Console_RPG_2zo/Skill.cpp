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
        cout << "정신이 한계에 다다랐다. 지금 이 힘을 쓰면 돌아올 수 없을 것 같다.\n";
        return;
    }

    player->setSan(player->getSan() - 10);

    int damage = static_cast<int>(player->getPower() * (1.0 + 0.1 * player->getLevel()))
        - monster->getDefence();
    if (damage < 1) damage = 1;

    TakeDamage(monster, damage);
    cout << "입술 사이로 낯선 언어가 흘러나온다. 손바닥 위에 지옥의 불꽃이 맺혔다.\n";
    cout << monster->getName() << "에게 " << damage << "의 피해를 입혔다.\n";
}

// ── 흑마법사 : 정신 과부화 
// SAN 15 소모. 데미지만큼 HP 흡수
// 흡수량 = damage * (0.1 * level)
void Skill_MindOverload(Player* player, Monster* monster)
{
    if (player->getSan() < 15)
    {
        cout << "정신이 한계에 다다랐다. 지금 이 힘을 쓰면 돌아올 수 없을 것 같다.\n";
        return;
    }

    player->setSan(player->getSan() - 15);

    int damage = player->getPower() - monster->getDefence();
    if (damage < 1) damage = 1;

    int heal = static_cast<int>(damage * (0.1 * player->getLevel()));

    TakeDamage(monster, damage);
    int newHp = player->getHp() + heal;
    if (newHp > player->getMaxHp()) newHp = player->getMaxHp();
    player->setHp(newHp);

    cout << "당신은 자신의 정신을 무기로 삼았다. 과부하된 의식의 파편이 " << monster->getName() << "를 향해 쏟아진다.\n";
    cout << monster->getName() << "에게 " << damage << "의 피해를 입혔다.\n";
    cout << monster->getName() << "의 생명력이 당신에게로 흘러든다. " << heal << "만큼 회복됐다.\n";
}


// ── 파계승 : 심안/무아일격 
// SAN 10 회복 후 기본 공격 1회. 쿨타임 있음
void Skill_MindStrike(Player* player, Monster* monster, int& turn_cycle)
{
    int newSan = player->getSan() + 10;
    if (newSan > player->getMaxSan()) newSan = player->getMaxSan();
    player->setSan(newSan);
    cout << "당신은 눈을 감는다. 세상의 소음이 사라지고, 오직 " << monster->getName() << "만이 남는다.\n";

    player->Attack(monster);

    int damage = DamageCalculate(player->getPower(), monster->getDefence());
    TakeDamage(monster, damage);
    cout << monster->getName() << "에게 " << damage << "의 피해를 입혔다.\n";
    
}


// ── 도적 : 안개 걸음
// 1턴 무적. 쿨타임 있음
void Skill_MistWalk(Player* player, int& turn_cycle)
{
    cout << "당신의 몸이 안개 속으로 녹아든다. 존재가 희미해지는 감각이 온몸을 감싼다.\n";
}

// ── 도박꾼 : 러시안 룰렛
// 최대 6번 선택. 나한테 쏘면 데미지 중첩(×1.2), 현재 HP 비례 자해 데미지
// 적한테 쏘면 총알 나가든 안 나가든 턴 종료
void Skill_RussianRoulette(Player* player, Monster* monster)
{
    cout << "리볼버가 손에 쥐어진다. 차가운 금속의 감촉이 오히려 머리를 맑게 한다. 부디 행운의 여신이 미소를 짓고 있기를.\n";

    float multiplier = 1.0f;
    int remainingChambers = 6;

    for (int shot = 0; shot < 6; shot++)
    {
        cout << "\n총신의 그림이 희미하게 빛난다. 리볼버가 천천히 돌아간다. 확률은 1/" << remainingChambers << ".\n";
        cout << "1. 나에게 방아쇠를 당긴다.\n";
        cout << "2. 적에게 방아쇠를 당긴다.\n";
        cout << "선택 : ";

        int choice;
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "올바른 행동이 아니다. 다시 한번 생각해보자.(숫자를 입력해 주세요)\n";
            shot--;
            continue;
        }

        bool isBullet = (rand() % remainingChambers == 0); // 1/remainingChambers 확률

        if (choice == 1) // 나에게
        {
            if (isBullet)
            {
                int selfDamage = player->getHp() / 2;
                TakeDamage(player, selfDamage);
                cout << "총알이 쏘아졌고, 내 몸을 강타하는 충격이 느껴진다. 불운의 여신이 조소를 보낸다.\n";
                cout << "선혈이 " << selfDamage << "만큼 흘러내렸다.\n";
                return;
            }
            else
            {
                remainingChambers--;   // 약실 하나 소진 → 확률 상승
                multiplier += 1.2f;
                cout << "총은 침묵했다. 총신에 아름다운 그림이 그려진다.\n";
            }
        }
        else if (choice == 2) // 적에게
        {
            if (isBullet)
            {
                int damage = static_cast<int>(
                    DamageCalculate(player->getPower(), monster->getDefence()) * multiplier);
                TakeDamage(monster, damage);
                cout << "총은 겨누어졌고, 총알은 발사되었다. 오늘의 행운은 " << monster->getName() << "의 것이 아니었다.\n";
                cout << monster->getName() << "에게 " << damage << "의 피해를 입혔다.\n";
            }
            else
            {
                cout << "총은 겨누어졌고, 침묵했다. 과감하지 못한 나에게 질책이 들리는 듯 하다. 총신의 그림이 흐릿해진다.\n";
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
            cout << "죽음의 냄새가 몸을 일깨운다. 고통이 점점 희미해져 간다.\n";
            return damage / 2;
        }
        return damage;

        // 파계승 — 명경지수 : SAN 90 이상 시 방어력 1.5배로 재계산
    case SkillID::CLEAR_MIND:
        if (player->getSan() > 90)
        {
            int newDamage = monster->getAttackPower() - static_cast<int>(player->getDefence() * 1.5);
            if (newDamage < 1) newDamage = 1;
            cout << "정신이 고요하다. 충격이 밀려오지만, 고요함이 그것을 받아낸다.\n";
            return newDamage;
        }
        return damage;

    default:
        return damage; // 해당 없는 패시브는 데미지 그대로
    }
}

