#include "BattleSystem.h"
#include "Skill.h"
#include "InventoryUI.h"
#include "LogManager.h"

#include "Allmonster.h"

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
    monster->Encounter();

    int OriginalAtk    = player->getPower();
    int OriginalDef    = player->getDefence();
    int OriginalSanDef = player->getSanDefence();

    int turn_cycle = 0;

    int skillLastUsed[3];
    skillLastUsed[0] = skillLastUsed[1] = skillLastUsed[2] = -100;
    bool isInvincible        = false;
    bool isDefending         = false;
    bool sanRecoveryPending  = false;
    int  sanPanicTurns       = 0;
    int  powerBattleBoost = 0;
    int  monsterAtkDebuff = 0;
    int  monsterDefDebuff = 0;
    int  effectiveAtk     = 0;
    int  effectiveDef     = 0;

    while (player->getHp() > 0 && monster->getHp() > 0)
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

        if (player->getSan() == 0 && sanPanicTurns == 0)
        {
            LogManager::TypePrint("\n당신의 정신은 현실을 감당하지 못하고 무너져 내린다.", 5);
            int roll = rand() % 100;

            if (roll < 5) // 5%: 즉사
            {
                LogManager::TypePrint("공포가 심장에게 종언을 고한다. 고통은 잦아들고 영원한 안식이 당신을 맞이한다.", 5);
                LogManager::PressEnter();
                player->setHp(0);
                skipPlayerTurn = true;
            }
            else if (roll < 35) // 30%: 3턴 랜덤행동
            {
                LogManager::TypePrint("공포가 의식을 잠식한다. 당신은 본능만이 남은 짐승이 되었다.", 5);
                LogManager::PressEnter();
                sanPanicTurns = 3;
            }
            else if (roll < 65) // 30%: 1턴 행동불가
            {
                LogManager::TypePrint("압도적인 공포가 온몸을 옥죄어 온다. 손가락 하나 움직일 수 없다.", 5);
                LogManager::PressEnter();
                sanRecoveryPending = true;
                skipPlayerTurn = true;
            }
            else // 35%: 최대 체력 50% 자해
            {
                int selfDmg = player->getMaxHp() / 2;
                if (selfDmg < 1) selfDmg = 1;
                int newHp = player->getHp() - selfDmg;
                if (newHp < 1) newHp = 1;
                LogManager::TypePrint("몸속의 피가 자유를 갈망한다. 당신은 정신이 들기도 전에 칼을 쥐고 스스로를 찔렀다.", 5);
                LogManager::TypePrint("선혈이 " + to_string(selfDmg) + "만큼 흘러내렸다.", 5);
                LogManager::PressEnter();
                player->setHp(newHp);
                player->setSan(10);
            }
        }

        if (!skipPlayerTurn && sanPanicTurns > 0)
        {
            skipPlayerTurn = true;
            LogManager::TypePrint("\n당신은 공포에 잠식된 짐승이 되어 몸이 이끄는 대로 움직인다. (" + to_string(sanPanicTurns) + "턴 남음)", 5);

            switch (rand() % 3)
            {
                case 0: // 공격
                {
                    LogManager::TypePrint("눈앞의 괴물밖에 보이지 않는다. 본능적으로 달려든다.", 5);
                    int damage = DamageCalculate(player->getPower(), monster->getDefence());
                    for (int i = 1; i <= 2; ++i)
                    {
                        SkillData sd = player->getSkillData(i);
                        if (sd.isPassive)
                            damage = Skill_PassiveOnAttack(sd.id, player, damage);
                    }
                    player->Attack(monster);
                    TakeDamage(monster, damage);
                    LogManager::TypePrint("→ " + monster->getName() + " 에게 " + to_string(damage) + "의 피해!", 5);
                    break;
                }
                case 1: // 방어
                {
                    LogManager::TypePrint("눈앞의 괴물밖에 보이지 않는다. 몸은 본능적으로 방어 자세를 취한다.", 5);
                    isDefending = true;
                    break;
                }
                case 2: // 도주
                {
                    int escapeChance = 30 + static_cast<int>((player->getSan() / 100.0) * 70);
                    if ((rand() % 100 + 1) <= escapeChance)
                    {
                        LogManager::TypePrint("당신은 어디로 가는지도 모른 채 달아났다. 본능만이 당신을 살렸다.", 5);
                        player->setPower(OriginalAtk);
                        player->setDefence(OriginalDef);
                        player->setSanDefence(OriginalSanDef);
                        return;
                    }
                    LogManager::TypePrint("아무것도 보이지 않는다. 다리는 땅을 내달렸으나, 활로를 찾지 못했다. 압도적인 공포와 함께 " + monster->getName() + " (이)가 천천히 다가온다.", 5);
                    break;
                }
            }

            sanPanicTurns--;
            if (sanPanicTurns == 0)
            {
                sanRecoveryPending = true;
                LogManager::TypePrint("머리를 뒤덮던 공포가 조금 가신다. 당신은 다시 자신을 되찾았다.", 5);
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
                    LogManager::TypePrint("\n→ " + monster->getName() + " 에게 " + to_string(damage) + "의 피해!", 5);
                    break;
                }

                case 2: // 방어
                {
                    LogManager::TypePrint("당신은 괴물의 다음 공격에 대비해 방어 자세를 취했다.", 5);
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
                    if (cin.fail())
                    {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        cout << "올바른 행동이 아니다. 다시 한번 생각해보자.(숫자를 입력해 주세요)\n";
                        continue;
                    }
                    if (skillSelect == 0)
                    {
                        continue;
                    }
                    else if (skillSelect == 1 || skillSelect == 2)
                    {
                        SkillData sd = player->getSkillData(skillSelect);

                        if (sd.isPassive)
                        {
                            LogManager::TypePrint(sd.name + "... 때가 되면 저절로 발휘될 것이다.", 5);
                            continue;
                        }

                        if (sd.cooltime > 0 && turn_cycle - skillLastUsed[skillSelect] < sd.cooltime)
                        {
                            int remaining = sd.cooltime - (turn_cycle - skillLastUsed[skillSelect]);
                            LogManager::TypePrint(sd.name + "... 아직은 때가 아닌 것 같다. (" + to_string(remaining) + "턴 남음)", 5);
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
                    LogManager::TypePrint("당신은 도주를 시도했다.", 5);

                    int  escapeChance = 30 + static_cast<int>((player->getSan() / 100.0) * 70);
                    int  randomCall   = rand() % 100 + 1;
                    bool escaped      = (randomCall <= escapeChance);

                    if (player->getSan() > 80)
                    {
                        if (escaped)
                            LogManager::TypePrint("당신은 침착하게 어둠 속에 몸을 숨기고 후퇴했다.", 5);
                        else
                            LogManager::TypePrint("당신은 침착하게 어둠 속에 몸을 숨기려 했으나, " + monster->getName() + " 에게 들켜버렸다.", 5);
                    }
                    else if (player->getSan() > 50)
                    {
                        if (escaped)
                            LogManager::TypePrint("떨리는 몸을 부여잡고 달렸다. 간신히 벗어났다.", 5);
                        else
                            LogManager::TypePrint("떨리는 몸을 부여잡고 달렸으나, 길을 헤매는 사이 " + monster->getName() + " 에게 따라잡혔다.", 5);
                    }
                    else if (player->getSan() > 10)
                    {
                        if (escaped)
                            LogManager::TypePrint("거의 제정신이 아닌 채로 달아났다. 어떻게 살아남았는지조차 알 수 없다.", 5);
                        else
                        {
                            LogManager::TypePrint("거의 제정신이 아닌 채로 달아나려 했으나, 돌부리에 걸려 쓰러졌다.", 5);
                            LogManager::TypePrint(monster->getName() + " (이)가 공포의 냄새를 맡고 다가온다.", 5);
                        }
                    }
                    else
                    {
                        if (escaped)
                            LogManager::TypePrint("당신은 어디로 가는지도 모른 채 달아났다. 본능만이 당신을 살렸다.", 5);
                        else
                            LogManager::TypePrint("아무것도 보이지 않는다. 다리는 땅을 내달렸으나, 활로를 찾지 못했다. 압도적인 공포와 함께 " + monster->getName() + " (이)가 천천히 다가온다.", 5);
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

        LogManager::PressEnter();
        if (player->getHp() <= 0) break;

        if (monster->getHp() <= 0)
        {
            LogManager::TypePrint("\n" + monster->getName() + " (이)가 쓰러진다. 전장에 고요가 찾아왔다.", 5);
            break;
        }

        LogManager::TypePrint("\n" + monster->getName() + " 의 차례...", 5);
        LogManager::PressEnter();

        if (isInvincible)
        {
            LogManager::TypePrint("안개 속에 숨어든 당신을 향한 " + monster->getName() + " 의 공격이 허공을 가른다.", 5);

            int counterDamage = DamageCalculate(player->getPower(), monster->getDefence());
            TakeDamage(monster, counterDamage);
            LogManager::TypePrint("허공을 가른 틈을 놓치지 않는다. " + monster->getName() + " 에게 " + to_string(counterDamage) + "의 피해!", 5);

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
                    LogManager::TypePrint("단단히 몸을 세운 방어 자세가 괴물의 충격을 흘려냈다.", 5);
                }

                TakeDamage(player, monsterDamage);
                LogManager::TypePrint("당신은 " + to_string(monsterDamage) + "의 피해를 입었다.", 5);
            }
        }

        if (player->getPower() < effectiveAtk)
            monsterAtkDebuff += effectiveAtk - player->getPower();
        if (player->getDefence() < effectiveDef)
            monsterDefDebuff += effectiveDef - player->getDefence();

        LogManager::PressEnter();
        LogManager::Clear();
        turn_cycle++;
    }

    if (player->getHp() <= 0)
    {
        LogManager::TypePrint("\n당신은 더 이상 몸을 가눌 수 없다. 의식이 흐려지는 가운데, 심연이 천천히 당신을 집어삼킨다.", 5);
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

        LogManager::TypePrint("\n전투의 흔적이 여실한 전장에 침묵이 내려앉는다. 괴물은 쓰러졌고, 당신은 아직 살아 숨쉬고 있다.", 5);


        player->setPower(OriginalAtk);
        player->setDefence(OriginalDef);
        player->setSanDefence(OriginalSanDef);

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
                LogManager::TypePrint("예리한 눈썰미로 괴물의 시체를 훑었다. 쓸 만한 것이 눈에 띈다.", 5);
            else
                LogManager::TypePrint("쓸 만한 것이 눈에 띈다.", 5);

            Item drop = (rand() % 2 == 0)
                ? Item::CreateHealPotion(player->getLevel())
                : Item::CreateSanPotion();
            LogManager::TypePrint(drop.getName() + "을 손에 넣었다.", 5);
            inventory.AddItem(drop);
        }
    }

}

void BattleSystem::EnterMissionMenu(Player& player, Inventory<Item>& inventory)
{
    if (stageProgress >= 15)
    {
        LogManager::TypePrint("모든 스토리를 완료했습니다.", 5);
        return;
    }

    while (true)
    {
        int choice;
        cout << " 1. 메인 스토리 진행 / 2. 지역 토벌(자유 전투) / 3. 돌아가기 \n";
        cout << "선택 : ";
        cin >> choice;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "올바른 행동이 아니다. 다시 한번 생각해보자.(숫자를 입력해 주세요)\n";
            continue;
        }

        if (choice == 1)
        {
            int chapter   = stageProgress / 3 + 1;
            int stageType = stageProgress % 3; // 0=일반, 1=중간보스, 2=최종보스

            if (stageType == 0)
            {
                if      (chapter == 1) LogManager::CH1();
                else if (chapter == 2) LogManager::CH2();
                else if (chapter == 3) LogManager::CH3();
                else if (chapter == 4) LogManager::CH4();
                else if (chapter == 5) LogManager::CH5();
            }

            if (stageType == 2)
            {
                if      (chapter == 1) LogManager::CH1_Boss();
                else if (chapter == 2) LogManager::CH2_Boss();
                else if (chapter == 3) LogManager::CH3_Boss();
                else if (chapter == 4) LogManager::CH4_Boss();
                else if (chapter == 5)
                {
                    LogManager::CH5_Choice();

                    int endingChoice = 0;
                    while (true)
                    {
                        cout << "선택 (1 / 2) : ";
                        cin >> endingChoice;
                        if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); continue; }
                        if (endingChoice == 1 || endingChoice == 2) break;
                    }

                    if (endingChoice == 1)
                    {
                        LogManager::HAPPY_END();
                        LogManager::PressEnter();
                        exit(0);
                    }

                    LogManager::Final_Boss_1();
                    LogManager::PressEnter();
                    LogManager::Final_Boss_2();
                }
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
                    vector<Item> rewards = Item::CreateChapterClearReward();
                    for (const Item& reward : rewards)
                    {
                        LogManager::TypePrint("[챕터 클리어 보상] " + reward.getName() + "!", 5);
                        inventory.AddItem(reward);
                    }
                }
            }
            return;
        }
        else if (choice == 2)
        {
            int chapter = stageProgress / 3 + 1;
            string stageStr = "CH" + to_string(chapter) + "_Normal_";
            stageStr += (rand() % 2 == 0) ? "A" : "B";
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
        if (!RunSingleBattle(player, inventory, new MutatedSlime(player.getLevel()))) return false;
        LogManager::TypePrint("\n또 다른 적이 나타났다!", 5);
        return RunSingleBattle(player, inventory, new PlagueServant(player.getLevel()));
    }
    else if (stage == "CH2_MidBoss")
    {
        if (!RunSingleBattle(player, inventory, new DimensionEye(player.getLevel()))) return false;
        LogManager::TypePrint("\n또 다른 적이 나타났다!", 5);
        return RunSingleBattle(player, inventory, new AbyssHive(player.getLevel()));
    }
    else if (stage == "CH3_MidBoss")
    {
        if (!RunSingleBattle(player, inventory, new BloodFanatic(player.getLevel()))) return false;
        LogManager::TypePrint("\n또 다른 적이 나타났다!", 5);
        return RunSingleBattle(player, inventory, new FanaticLeader(player.getLevel()));
    }
    else if (stage == "CH4_MidBoss")
    {
        if (!RunSingleBattle(player, inventory, new FleshFusion(player.getLevel()))) return false;
        LogManager::TypePrint("\n또 다른 적이 나타났다!", 5);
        return RunSingleBattle(player, inventory, new CorruptedKnight(player.getLevel()));
    }
    else if (stage == "CH5_MidBoss")
    {
        if (!RunSingleBattle(player, inventory, new AltarGuardian(player.getLevel()))) return false;
        LogManager::TypePrint("\n또 다른 적이 나타났다!", 5);
        return RunSingleBattle(player, inventory, new SoreArkadia(player.getLevel()));
    }
    else if (stage == "CH5_MainBoss")
    {
        RunFinalBossBattle(&player, inventory);
        return false;
    }

    Monster* monster = nullptr;

    if      (stage == "CH1_Normal")   monster = new VoidHound(player.getLevel());
    else if (stage == "CH2_Normal")   monster = new AbyssRemnant(player.getLevel());
    else if (stage == "CH3_Normal")   monster = new AbyssFanatic(player.getLevel());
    else if (stage == "CH4_Normal")   monster = new TwistedGuard(player.getLevel());
    else if (stage == "CH5_Normal")   monster = new VoidEcho(player.getLevel());

    else if (stage == "CH1_MainBoss") monster = new CorpseGolem(player.getLevel());
    else if (stage == "CH2_MainBoss") monster = new Oblivion(player.getLevel());
    else if (stage == "CH3_MainBoss") monster = new Malachai(player.getLevel());
    else if (stage == "CH4_MainBoss") monster = new Arkadia(player.getLevel());
    else if (stage == "CH5_MainBoss") monster = nullptr; // RunFinalBossBattle 에서 처리

    else if (stage == "CH1_Normal_A") monster = new VoidHound(player.getLevel());
    else if (stage == "CH1_Normal_B") monster = new MutatedSlime(player.getLevel());
    else if (stage == "CH2_Normal_A") monster = new AbyssRemnant(player.getLevel());
    else if (stage == "CH2_Normal_B") monster = new DimensionEye(player.getLevel());
    else if (stage == "CH3_Normal_A") monster = new AbyssFanatic(player.getLevel());
    else if (stage == "CH3_Normal_B") monster = new BloodFanatic(player.getLevel());
    else if (stage == "CH4_Normal_A") monster = new TwistedGuard(player.getLevel());
    else if (stage == "CH4_Normal_B") monster = new FleshFusion(player.getLevel());
    else if (stage == "CH5_Normal_A") monster = new VoidEcho(player.getLevel());
    else if (stage == "CH5_Normal_B") monster = new AltarGuardian(player.getLevel());

    return RunSingleBattle(player, inventory, monster);
}
