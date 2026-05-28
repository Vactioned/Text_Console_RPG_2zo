#include "BattleSystem.h"
#include "Skill.h"
#include "InventoryUI.h"
#include "LogManager.h"

#include <iostream>
#include <cstdlib>

using namespace std;

int DamageCalculate(int attack, int defence)
{
    int damage = attack - defence;
    if (damage < 1) damage = 1;
    return damage;
}

void BattleStart(Player* player, Monster* monster, Inventory<Item>& inventory)
{
    // TODO: 몬스터 조우 대사 출력 (몬스터 담당자 협업 예정)

    int OriginalAtk    = player->getPower();
    int OriginalDef    = player->getDefence();
    int OriginalSanDef = player->getSanDefence();

    int turn_cycle = 0;

    int skillLastUsed[3];
    skillLastUsed[0] = skillLastUsed[1] = skillLastUsed[2] = -100;
    bool isInvincible     = false;
    bool isDefending      = false;
    int  sanPanicTurns    = 0;
    int  powerBattleBoost = 0;

    while (player->getHp() > 0 && monster->getHp() > 0)
    {
        isDefending = false;

        {
            int san          = player->getSan();
            int baseAtk      = OriginalAtk + powerBattleBoost;
            int effectiveAtk = baseAtk;
            int effectiveDef = OriginalDef;

            if (san <= 10)
            {
                effectiveAtk = static_cast<int>(baseAtk * 0.80);
                effectiveDef = static_cast<int>(OriginalDef * 0.80);
            }
            else if (san <= 30)
            {
                effectiveAtk = static_cast<int>(baseAtk * 0.90);
                effectiveDef = static_cast<int>(OriginalDef * 0.90);
            }
            else if (san <= 50)
            {
                effectiveDef = static_cast<int>(OriginalDef * 0.90);
            }

            player->setPower(effectiveAtk);
            player->setDefence(effectiveDef);
        }

        bool skipPlayerTurn = false;

        if (player->getSan() == 0 && sanPanicTurns == 0)
        {
            cout << "\n[광기] 정신이 완전히 무너졌다!\n";
            int roll = rand() % 100;

            if (roll < 5) // 5%: 즉사
            {
                cout << "극도의 공포가 심장을 멈추게 했다... 당신은 쓰러졌다.\n";
                player->setHp(0);
                skipPlayerTurn = true;
            }
            else if (roll < 35) // 30%: 3턴 랜덤행동
            {
                cout << "[패닉] 공포에 사로잡혀 스스로를 제어할 수 없다! (3턴간 랜덤 행동)\n";
                sanPanicTurns = 3;
            }
            else if (roll < 65) // 30%: 1턴 행동불가
            {
                cout << "[공포] 극도의 공포로 몸이 굳어 행동할 수 없다!\n";
                player->setSan(10);
                skipPlayerTurn = true;
            }
            else // 35%: 최대 체력 50% 자해
            {
                int selfDmg = player->getMaxHp() / 2;
                if (selfDmg < 1) selfDmg = 1;
                int newHp = player->getHp() - selfDmg;
                if (newHp < 1) newHp = 1;
                cout << "[자해] 공포에 스스로를 해쳤다! " << selfDmg << "의 피해!\n";
                player->setHp(newHp);
                player->setSan(10);
            }
        }

        if (!skipPlayerTurn && sanPanicTurns > 0)
        {
            skipPlayerTurn = true;
            cout << "\n[광기] (" << (4 - sanPanicTurns) << "/3) 공포에 사로잡혀 제멋대로 행동한다!\n";

            switch (rand() % 3)
            {
                case 0: // 공격
                {
                    cout << "정신 없이 공격한다!\n";
                    int damage = DamageCalculate(player->getPower(), monster->getDefence());
                    for (int i = 1; i <= 2; ++i)
                    {
                        SkillData sd = player->getSkillData(i);
                        if (sd.isPassive)
                            damage = Skill_PassiveOnAttack(sd.id, player, damage);
                    }
                    player->Attack(monster);
                    TakeDamage(monster, damage);
                    cout << "→ " << monster->getName() << "에게 " << damage << "의 피해!\n";
                    break;
                }
                case 1: // 방어
                {
                    cout << "공포에 질려 웅크린다!\n";
                    isDefending = true;
                    break;
                }
                case 2: // 도주
                {
                    int escapeChance = 30 + static_cast<int>((player->getSan() / 100.0) * 70);
                    if ((rand() % 100 + 1) <= escapeChance)
                    {
                        cout << "당신은 패닉에 빠져 자신이 어디로 가는지도 모른 채 넘어지고 기어가며 적으로부터 달아나는 데 성공했다.\n";
                        player->setPower(OriginalAtk);
                        player->setDefence(OriginalDef);
                        player->setSanDefence(OriginalSanDef);
                        return;
                    }
                    cout << "당신은 패닉에 빠져 도망치려 했지만 다리가 꼬여 넘어졌다. 벌벌 떠는 당신을 향해 " << monster->getName() << "(이)가 압도적인 공포와 함께 천천히 다가온다.\n";
                    break;
                }
            }

            sanPanicTurns--;
            if (sanPanicTurns == 0)
            {
                player->setSan(10);
                cout << "[회복] 정신을 차렸다.\n";
            }
        }

        if (!skipPlayerTurn)
        {
        cout << "당신의 차례가 되었다. 당신은...\n";

        int select;

        while (true)
        {
            cout << "1. 적에게 공격을 가한다.\n";
            cout << "2. 방어 자세를 취한다.\n";
            cout << "3. 기술을 사용한다.\n";
            cout << "4. 가방을 연다.\n";
            cout << "5. 도주를 시도한다.\n";
            cout << "선택 : ";
            cin >> select;
            cout << "\n\n";

            switch (select)
            {
                case 1: // 공격
                {
                    int damage = DamageCalculate(player->getPower(), monster->getDefence());
                    for (int i = 1; i <= 2; ++i)
                    {
                        SkillData sd = player->getSkillData(i);
                        if (sd.isPassive)
                            damage = Skill_PassiveOnAttack(sd.id, player, damage);
                    }
                    player->Attack(monster);
                    TakeDamage(monster, damage);
                    cout << "\n→ " << monster->getName() << "에게 " << damage << "의 피해!\n";
                    break;
                }

                case 2: // 방어
                {
                    cout << "방어 자세를 취했다. 이번 몬스터 공격의 피해가 절반으로 줄어든다.\n";
                    isDefending = true;
                    break;
                }

                case 3: // 스킬
                {
                    cout << "=== 기술 선택 ===\n";
                    for (int i = 1; i <= 2; i++)
                    {
                        SkillData sd = player->getSkillData(i);
                        cout << i << ". [" << sd.name << "]";
                        if (sd.isPassive)
                            cout << "(패시브)";
                        cout << " - " << sd.description << "\n";
                    }

                    cout << "0. 돌아가기\n";
                    cout << "선택 : ";

                    int skillSelect;
                    cin >> skillSelect;
                    if (skillSelect == 0)
                    {
                        continue;
                    }
                    else if (skillSelect == 1 || skillSelect == 2)
                    {
                        SkillData sd = player->getSkillData(skillSelect);

                        if (sd.isPassive)
                        {
                            cout << "[" << sd.name << "](은)는 전투 중 자동으로 발동될 것 이다.\n";
                            continue;
                        }

                        if (sd.cooltime > 0 && turn_cycle - skillLastUsed[skillSelect] < sd.cooltime)
                        {
                            int remaining = sd.cooltime - (turn_cycle - skillLastUsed[skillSelect]);
                            cout << "[" << sd.name << "] 재사용 대기 중. ("
                                << remaining << "턴 남음)\n";
                            continue;
                        }

                        player->useSkill(skillSelect, monster, turn_cycle);

                        if (sd.id == SkillID::MIST_WALK)
                            isInvincible = true;

                        if (sd.cooltime > 0)
                            skillLastUsed[skillSelect] = turn_cycle;
                    }
                    else
                    {
                        cout << "올바른 행동이 아니다. 다시 한번 생각해보자.\n";
                        continue;
                    }
                    break;
                }

                case 4: // 아이템
                {
                    int powerBefore = player->getPower();
                    InventoryUI inventoryUI;
                    bool used = inventoryUI.Open(inventory, player, true, monster);
                    if (!used)
                        continue;
                    powerBattleBoost += player->getPower() - powerBefore;
                    break;
                }

                case 5: // 도주
                {
                    cout << "당신은 도주를 시도했다.\n";

                    int  escapeChance = 30 + static_cast<int>((player->getSan() / 100.0) * 70);
                    int  randomCall   = rand() % 100 + 1;
                    bool escaped      = (randomCall <= escapeChance);

                    if (player->getSan() > 80)
                    {
                        if (escaped)
                            cout << "당신은 침착하게 어둠 속에 몸을 숨기고 후퇴하였다.\n";
                        else
                            cout << "당신은 침착하게 어둠 속에 몸을 숨기고 후퇴하려 했으나 " << monster->getName() << "에게 들켜 실패하였다.\n";
                    }
                    else if (player->getSan() > 50)
                    {
                        if (escaped)
                            cout << "당신은 떨리는 몸을 부여잡고 달려서 간신히 도주하였다.\n";
                        else
                            cout << "당신은 떨리는 몸을 부여잡고 달려서 도주하려 했으나 길을 헤매는 사이 " << monster->getName() << "에게 따라잡혔다.\n";
                    }
                    else if (player->getSan() > 10)
                    {
                        if (escaped)
                            cout << "당신은 거의 제정신이 아닌 상태로 꼴사납게 도망치는 데 성공하였다.\n";
                        else
                        {
                            cout << "당신은 거의 제정신이 아닌 상태로 도망치려 하였으나 돌부리에 걸려 넘어지고 말았다.\n";
                            cout << monster->getName() << "(이)가 공포의 냄새를 맡고 당신에게 다가온다.\n";
                        }
                    }
                    else
                    {
                        if (escaped)
                            cout << "당신은 패닉에 빠져 자신이 어디로 가는지도 모른 채 넘어지고 기어가며 적으로부터 달아나는 데 성공했다.\n";
                        else
                            cout << "당신은 패닉에 빠져 도망치려 했지만 다리가 꼬여 넘어졌다. 벌벌 떠는 당신을 향해 " << monster->getName() << "(이)가 압도적인 공포와 함께 천천히 다가온다.\n";
                    }

                    if (escaped)
                    {
                        player->setPower(OriginalAtk);
                        player->setDefence(OriginalDef);
                        player->setSanDefence(OriginalSanDef);
                        return;
                    }
                    break;
                }

                default:
                {
                    cout << "올바른 행동이 아니다. 다시 한번 생각해보자.\n";
                    continue;
                }
            }
            break;
        }
        } // end if (!skipPlayerTurn)

        if (player->getHp() <= 0) break;

        if (monster->getHp() <= 0)
        {
            cout << "\n" << monster->getName() << "(이)가 쓰러졌다!\n";
            break;
        }

        cout << "\n" << monster->getName() << "의 차례...\n";

        if (isInvincible)
        {
            cout << "안개 속에 몸을 숨긴 당신에게 " << monster->getName() << "의 공격이 빗나갔다.\n";

            int counterDamage = DamageCalculate(player->getPower(), monster->getDefence());
            TakeDamage(monster, counterDamage);
            cout << "반격! " << monster->getName() << "에게 " << counterDamage << "의 피해!\n";

            isInvincible = false;
        }
        else
        {
            int monsterDamage = 0;
            if (rand() % 10 >= 3)
                monsterDamage = monster->NormalAttack(player);
            else
                monsterDamage = monster->SpecialAttack(player);

            if (monsterDamage > 0)
            {
                for (int i = 1; i <= 2; ++i)
                {
                    SkillData sd = player->getSkillData(i);
                    if (sd.isPassive)
                        monsterDamage = Skill_PassiveOnHit(sd.id, player, monster, monsterDamage);
                }

                if (isDefending)
                {
                    monsterDamage /= 2;
                    cout << "방어 자세! 받는 피해가 절반으로 줄었다.\n";
                }

                TakeDamage(player, monsterDamage);
            }
        }

        turn_cycle++;
    }

    if (player->getHp() <= 0)
    {
        cout << "\n당신은 쓰러졌다...\n";
        cout << "\n========================================\n";
        cout << "               GAME  OVER               \n";
        cout << "========================================\n";
        cout << "[ 엔터(Enter)를 누르면 종료합니다... ]";
        cin.ignore();
        cin.get();
        exit(0);
    }
    else
    {
        cout << "\n전투에서 승리하였다!\n";

        LevelUp levelUp;
        levelUp.AddExp(player, 50);

        int dropChance = 30;
        for (int i = 1; i <= 2; ++i)
        {
            SkillData sd = player->getSkillData(i);
            if (sd.id == SkillID::PLUNDER)
            {
                dropChance = 60;
                break;
            }
        }

        if (rand() % 100 < dropChance)
        {
            if (dropChance > 30)
                cout << "[약탈] 예리한 손놀림으로 전리품을 챙겼다!\n";

            Item drop = (rand() % 2 == 0)
                ? Item::CreateHealPotion()
                : Item::CreateSanPotion();
            cout << "[아이템 획득] " << drop.getName() << "!\n";
            inventory.AddItem(drop);
        }
    }

    player->setPower(OriginalAtk);
    player->setDefence(OriginalDef);
    player->setSanDefence(OriginalSanDef);
}

void BattleSystem::EnterMissionMenu(Player& player, Inventory<Item>& inventory)
{
    if (stageProgress >= 15)
    {
        cout << "모든 스토리를 완료했습니다.\n";
        return;
    }

    while (true)
    {
        int choice;
        cout << " 1. 메인 스토리 진행 / 2. 지역 토벌(자유 전투) / 3. 돌아가기 \n";
        cout << "선택 : ";
        cin >> choice;

        if (choice == 1)
        {
            int chapter   = stageProgress / 3 + 1;
            int stageType = stageProgress % 3; // 0=일반, 1=중간보스, 2=최종보스

            if (stageType == 0)
            {
                if (chapter == 1) LogManager::CH1();
                // TODO: CH2~5 스토리 함수 추가 필요 (LogManager 담당자)
            }

            if (stageType == 2)
            {
                if (chapter == 1) LogManager::CH1_Boss();
                // TODO: CH2~5 보스 연출 함수 추가 필요 (LogManager 담당자)
            }

            string stageStr = "CH" + to_string(chapter) + "_";
            if      (stageType == 0) stageStr += "Normal";
            else if (stageType == 1) stageStr += "MidBoss";
            else                     stageStr += "MainBoss";

            if (StartBattle(player, inventory, stageStr))
            {
                stageProgress++;

                if (stageType == 2)
                {
                    Item reward = Item::CreateChapterClearReward();
                    cout << "[챕터 클리어 보상] " << reward.getName() << "!\n";
                    inventory.AddItem(reward);
                }
            }
            return;
        }
        else if (choice == 2)
        {
            int chapter = stageProgress / 3 + 1;
            string stageStr = "CH" + to_string(chapter) + "_Normal_";
            stageStr += (rand() % 2 == 0) ? "A" : "B";
            cout << "[CH" << chapter << " 지역] 일반 몬스터가 나타납니다.\n";
            StartBattle(player, inventory, stageStr);
            return;
        }
        else if (choice == 3)
        {
            return;
        }
        else
        {
            cout << "잘못된 선택입니다.\n";
        }
    }
}

bool BattleSystem::RunSingleBattle(Player& player, Inventory<Item>& inventory,
                                    Monster* monster)
{
    if (monster == nullptr)
    {
        cout << "[준비 중] 아직 해당 구역의 몬스터가 배치되지 않았습니다.\n";
        return false;
    }

    BattleStart(&player, monster, inventory);
    bool won = (monster->getHp() <= 0);
    delete monster;
    return won;
}

bool BattleSystem::StartBattle(Player& player, Inventory<Item>& inventory,
                                const string& stage)
{
    if (stage == "CH1_MidBoss")
    {
        if (!RunSingleBattle(player, inventory, nullptr)) return false; // TODO: CH1 일반 B
        cout << "\n또 다른 적이 나타났다!\n";
        return RunSingleBattle(player, inventory, nullptr);             // TODO: CH1 하수인급
    }
    else if (stage == "CH2_MidBoss")
    {
        if (!RunSingleBattle(player, inventory, nullptr)) return false; // TODO: CH2 일반 B
        cout << "\n또 다른 적이 나타났다!\n";
        return RunSingleBattle(player, inventory, nullptr);             // TODO: CH2 하수인급
    }
    else if (stage == "CH3_MidBoss")
    {
        if (!RunSingleBattle(player, inventory, nullptr)) return false; // TODO: CH3 일반 B
        cout << "\n또 다른 적이 나타났다!\n";
        return RunSingleBattle(player, inventory, nullptr);             // TODO: CH3 하수인급
    }
    else if (stage == "CH4_MidBoss")
    {
        if (!RunSingleBattle(player, inventory, nullptr)) return false; // TODO: CH4 일반 B
        cout << "\n또 다른 적이 나타났다!\n";
        return RunSingleBattle(player, inventory, nullptr);             // TODO: CH4 하수인급
    }
    else if (stage == "CH5_MidBoss")
    {
        if (!RunSingleBattle(player, inventory, nullptr)) return false; // TODO: CH5 일반 B
        cout << "\n또 다른 적이 나타났다!\n";
        return RunSingleBattle(player, inventory, nullptr);             // TODO: CH5 하수인급
    }

    Monster* monster = nullptr;

    if      (stage == "CH1_Normal")   monster = nullptr; // TODO: CH1 일반 A
    else if (stage == "CH2_Normal")   monster = nullptr; // TODO: CH2 일반 A
    else if (stage == "CH3_Normal")   monster = nullptr; // TODO: CH3 일반 A
    else if (stage == "CH4_Normal")   monster = nullptr; // TODO: CH4 일반 A
    else if (stage == "CH5_Normal")   monster = nullptr; // TODO: CH5 일반 A

    else if (stage == "CH1_MainBoss") monster = nullptr; // TODO: CH1 보스급
    else if (stage == "CH2_MainBoss") monster = nullptr; // TODO: CH2 보스급
    else if (stage == "CH3_MainBoss") monster = nullptr; // TODO: CH3 보스급
    else if (stage == "CH4_MainBoss") monster = nullptr; // TODO: CH4 보스급
    else if (stage == "CH5_MainBoss") monster = nullptr; // TODO: CH5 보스급

    else if (stage == "CH1_Normal_A") monster = nullptr; // TODO: CH1 일반 A (자유전투)
    else if (stage == "CH1_Normal_B") monster = nullptr; // TODO: CH1 일반 B (자유전투)
    else if (stage == "CH2_Normal_A") monster = nullptr; // TODO: CH2 일반 A (자유전투)
    else if (stage == "CH2_Normal_B") monster = nullptr; // TODO: CH2 일반 B (자유전투)
    else if (stage == "CH3_Normal_A") monster = nullptr; // TODO: CH3 일반 A (자유전투)
    else if (stage == "CH3_Normal_B") monster = nullptr; // TODO: CH3 일반 B (자유전투)
    else if (stage == "CH4_Normal_A") monster = nullptr; // TODO: CH4 일반 A (자유전투)
    else if (stage == "CH4_Normal_B") monster = nullptr; // TODO: CH4 일반 B (자유전투)
    else if (stage == "CH5_Normal_A") monster = nullptr; // TODO: CH5 일반 A (자유전투)
    else if (stage == "CH5_Normal_B") monster = nullptr; // TODO: CH5 일반 B (자유전투)

    return RunSingleBattle(player, inventory, monster);
}
