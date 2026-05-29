#include "FinalBoss.h"
#include "BattleSystem.h"
#include "Skill.h"
#include "LogManager.h"
#include "InventoryUI.h"

#include <iostream>
#include <cstdlib>

using namespace std;

// ================================================================
// FinalBoss 몬스터
// ================================================================

FinalBoss::FinalBoss(int playerlevel)
    : Monster(9999, 999, 99, 99, "[????]")
{
}

void FinalBoss::Encounter()
{
    cout << "\n깨어진 하늘의 파편 너머로, 가늠조차 되지 않는 것이 강림하기 시작한다." << endl;
    cout << "그 압도적인 존재감 앞에 나의 존재는 한없이 희미해졌고, 무력함이 전신을 적셨다." << endl;
    cout << "스스로를 기만하며 떨리는 손으로 무기를 쥐어든다." << endl;
    cout << "[????] 가 세계의 종언을 고한다.\n" << endl;
}

// 물리 100 고정 반환 + 정신력 20 직접 처리
int FinalBoss::NormalAttack(Player* player)
{
    LogManager::TypePrint("[????] 이(가) 현실을 비틀어 당신을 짓누릅니다.", 5);

    if (player != nullptr)
    {
        int sanDamage = 20;
        player->setSan(player->getSan() - sanDamage);
        LogManager::TypePrint("\n무언가 당신의 정신을 갉아먹는다. 정신력이 " + to_string(sanDamage) + "만큼 감소합니다.", 5);
    }

    return 100;
}

// 물리 100 고정 반환 + 정신력 30 직접 처리
int FinalBoss::SpecialAttack(Player* player)
{
    LogManager::TypePrint("[????] 이(가) 당신의 존재를 부정합니다.", 5);

    if (player != nullptr)
    {
        int sanDamage = 30;
        player->setSan(player->getSan() - sanDamage);
        LogManager::TypePrint("\n심연이 당신의 정신을 집어삼킨다. 정신력이 " + to_string(sanDamage) + "만큼 감소합니다.", 5);
    }

    return 100;
}

// ================================================================
// 이벤트 필패전
// - 보스 체력 매 턴 초기화 (필패)
// - SAN=0 시 무조건 자해 발생
// - 자해 2회 누적 시 전투 종료 트리거
// - 피해는 최대 체력의 절반 + 1 아래로 내려가지 않음
// ================================================================

void RunFinalBossBattle(Player* player, Inventory<Item>& inventory)
{
    FinalBoss boss(player->getLevel());
    boss.Encounter();

    int OriginalAtk    = player->getPower();
    int OriginalDef    = player->getDefence();
    int OriginalSanDef = player->getSanDefence();

    int turn_cycle = 0;
    int skillLastUsed[3];
    skillLastUsed[0] = skillLastUsed[1] = skillLastUsed[2] = -100;

    bool isInvincible       = false;
    bool isDefending        = false;
    bool sanRecoveryPending = false;
    int  powerBattleBoost   = 0;
    int  monsterAtkDebuff   = 0;
    int  monsterDefDebuff   = 0;
    int  effectiveAtk       = 0;
    int  effectiveDef       = 0;
    int  selfHarmCount      = 0;
    bool selfHarmTrigger    = false;

    while (player->getHp() > 0)
    {
        isDefending = false;

        {
            int san     = player->getSan();
            int baseAtk = OriginalAtk + powerBattleBoost - monsterAtkDebuff;
            int baseDef = OriginalDef - monsterDefDebuff;
            effectiveAtk = baseAtk;
            effectiveDef = baseDef;

            if (san <= 10)
            {
                effectiveAtk = static_cast<int>(baseAtk * 0.80);
                effectiveDef = static_cast<int>(baseDef * 0.80);
            }
            else if (san <= 30)
            {
                effectiveAtk = static_cast<int>(baseAtk * 0.90);
                effectiveDef = static_cast<int>(baseDef * 0.90);
            }
            else if (san <= 50)
            {
                effectiveDef = static_cast<int>(baseDef * 0.90);
            }

            player->setPower(effectiveAtk);
            player->setDefence(effectiveDef);
        }

        bool skipPlayerTurn = false;

        if (sanRecoveryPending)
        {
            player->setSan(10);
            sanRecoveryPending = false;
        }

        // SAN=0 시 무조건 자해
        if (player->getSan() == 0)
        {
            LogManager::TypePrint("\n당신의 정신은 현실을 감당하지 못하고 무너져 내린다.", 5);

            int selfDmg = player->getMaxHp() / 2;
            if (selfDmg < 1) selfDmg = 1;
            int newHp = player->getHp() - selfDmg;
            if (newHp < 1) newHp = 1;

            LogManager::TypePrint("몸속의 피가 자유를 갈망한다. 당신은 정신이 들기도 전에 칼을 쥐고 스스로를 찔렀다.", 5);
            LogManager::TypePrint("선혈이 " + to_string(selfDmg) + "만큼 흘러내렸다.", 5);
            LogManager::PressEnter();

            player->setHp(newHp);
            player->setSan(10);
            skipPlayerTurn = true;

            selfHarmCount++;
            if (selfHarmCount >= 2)
            {
                selfHarmTrigger = true;
                break;
            }
        }

        if (!skipPlayerTurn)
        {
            LogManager::TypePrint("당신의 차례가 되었다. 당신은...", 5);
            int select;

            while (true)
            {
                player->PrintPlayerStatus();
                cout << "1. 적에게 공격을 가한다.\n";
                cout << "2. 방어 자세를 취한다.\n";
                cout << "3. 기술을 사용한다.\n";
                cout << "4. 가방을 연다.\n";
                cout << "5. 도주를 시도한다.\n";
                cout << "================================================================" << endl;
                cout << "선택 : ";
                cin >> select;
                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "올바른 행동이 아니다. 다시 한번 생각해보자.(숫자를 입력해 주세요)\n";
                    continue;
                }
                cout << "\n\n";

                switch (select)
                {
                    case 1:
                    {
                        int damage = DamageCalculate(player->getPower(), boss.getDefence());
                        for (int i = 1; i <= 2; ++i)
                        {
                            SkillData sd = player->getSkillData(i);
                            if (sd.isPassive) damage = Skill_PassiveOnAttack(sd.id, player, damage);
                        }
                        player->Attack(&boss);
                        TakeDamage(&boss, damage);
                        LogManager::TypePrint("\n→ [????] 에게 " + to_string(damage) + "의 피해!", 5);
                        boss.setHp(boss.getMaxhp());
                        LogManager::TypePrint("[????] 에게 입힌 상처가 눈 깜짝할 사이에 아물어 버린다.", 5);
                        break;
                    }
                    case 2:
                        LogManager::TypePrint("당신은 괴물의 다음 공격에 대비해 방어 자세를 취했다.", 5);
                        isDefending = true;
                        break;
                    case 3:
                    {
                        cout << "=== 기술 선택 ===\n";
                        for (int i = 1; i <= 2; i++)
                        {
                            SkillData sd = player->getSkillData(i);
                            cout << i << ". [" << sd.name << "]";
                            if (sd.isPassive) cout << "(패시브)";
                            cout << " - " << sd.description << "\n";
                        }
                        cout << "0. 돌아가기\n";
                        cout << "선택 : ";
                        int skillSelect;
                        cin >> skillSelect;
                        if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); continue; }
                        if (skillSelect == 0) continue;
                        if (skillSelect == 1 || skillSelect == 2)
                        {
                            SkillData sd = player->getSkillData(skillSelect);
                            if (sd.isPassive) { LogManager::TypePrint(sd.name + "... 때가 되면 저절로 발휘될 것이다.", 5); continue; }
                            if (sd.cooltime > 0 && turn_cycle - skillLastUsed[skillSelect] < sd.cooltime)
                            {
                                int remaining = sd.cooltime - (turn_cycle - skillLastUsed[skillSelect]);
                                LogManager::TypePrint(sd.name + "... 아직은 때가 아닌 것 같다. (" + to_string(remaining) + "턴 남음)", 5);
                                continue;
                            }
                            player->useSkill(skillSelect, &boss, turn_cycle);
                            if (sd.id == SkillID::MIST_WALK) isInvincible = true;
                            if (sd.cooltime > 0) skillLastUsed[skillSelect] = turn_cycle;
                            boss.setHp(boss.getMaxhp());
                            LogManager::TypePrint("[????] 에게 입힌 상처가 눈 깜짝할 사이에 아물어 버린다.", 5);
                        }
                        else { cout << "올바른 행동이 아니다. 다시 한번 생각해보자.\n"; continue; }
                        break;
                    }
                    case 4:
                    {
                        int powerBefore = player->getPower();
                        InventoryUI inventoryUI;
                        bool used = inventoryUI.Open(inventory, player, true, &boss);
                        if (!used) continue;
                        powerBattleBoost += player->getPower() - powerBefore;
                        break;
                    }
                    case 5:
                        LogManager::TypePrint("도망치려 했지만, [????] 의 존재가 현실을 장악하고 있다. 이 자리를 벗어날 수 없다.", 5);
                        break;
                    default:
                        cout << "올바른 행동이 아니다. 다시 한번 생각해보자.\n";
                        continue;
                }
                break;
            }
        }

        LogManager::PressEnter();
        if (player->getHp() <= 0) break;

        LogManager::TypePrint("\n[????] 의 차례...", 5);
        LogManager::PressEnter();

        if (isInvincible)
        {
            LogManager::TypePrint("[????] 의 공격이 허공을 가른다. 그러나 이것이 의미 있는 일인지조차 알 수 없다.", 5);
            isInvincible = false;
        }
        else
        {
            int monsterDamage = 0;
            if (rand() % 10 >= 3)
                monsterDamage = boss.NormalAttack(player);
            else
                monsterDamage = boss.SpecialAttack(player);

            if (monsterDamage > 0)
            {
                for (int i = 1; i <= 2; ++i)
                {
                    SkillData sd = player->getSkillData(i);
                    if (sd.isPassive)
                        monsterDamage = Skill_PassiveOnHit(sd.id, player, &boss, monsterDamage);
                }
                if (isDefending)
                {
                    monsterDamage /= 2;
                    LogManager::TypePrint("단단히 몸을 세운 방어 자세가 괴물의 충격을 흘려냈다.", 5);
                }

                TakeDamage(player, monsterDamage);
                LogManager::TypePrint("당신은 " + to_string(monsterDamage) + "의 피해를 입었다.", 5);

                // 한 번의 피해로 최대 체력의 절반 + 1 아래로 내려가지 않음
                int minHp = player->getMaxHp() / 2 + 1;
                if (player->getHp() < minHp)
                    player->setHp(minHp);
            }
        }

        if (player->getPower() < effectiveAtk) monsterAtkDebuff += effectiveAtk - player->getPower();
        if (player->getDefence() < effectiveDef) monsterDefDebuff += effectiveDef - player->getDefence();

        LogManager::PressEnter();
        LogManager::Clear();
        turn_cycle++;
    }

    // 필패전 종료 — BAD_END
    player->setPower(OriginalAtk);
    player->setDefence(OriginalDef);
    player->setSanDefence(OriginalSanDef);

    if (selfHarmTrigger)
        LogManager::TypePrint("\n스스로를 두 번이나 찌른 손이 떨린다. 더 이상 싸울 의지가 남아있지 않다.", 5);
    else
        LogManager::TypePrint("\n당신은 더 이상 몸을 가눌 수 없다. 그 존재 앞에 인간의 의지는 아무 의미도 없었다.", 5);

    LogManager::BAD_END();
    LogManager::PressEnter();
    exit(0);
}
