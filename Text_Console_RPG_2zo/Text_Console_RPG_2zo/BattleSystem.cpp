#include "BattleSystem.h"
#include "Skill.h"

#include <iostream>
#include <ctime>    // rand 사용 시 main에서 srand 호출 필요
#include <cstdlib>

using namespace std;

// ================================================================
// 데미지 계산
// : attack - defence, 최솟값 1 보장
// ================================================================
int DamageCalculate(int attack, int defence)
{
    int damage = attack - defence;
    if (damage < 1) damage = 1;
    return damage;
}

// ================================================================
// 전투 시작
// ================================================================
void BattleStart(Player* player, Monster* monster)
{
    // TODO: 몬스터 조우 대사 출력 (몬스터 담당자 협업 예정)

    int OriginalDef = player->getDefence();
    int OriginalAtk = player->getPower();
    int OriginalSanDef = player->getSanDefence();

    int turn_cycle = 0;

    int skillLastUsed[3];
    skillLastUsed[0] = skillLastUsed[1] = skillLastUsed[2] = -100;
    bool isInvincible = false;

    while (player->getHp() > 0 && monster->getHp() > 0)
    {
        cout << "당신의 차례가 되었다. 당신은...\n";

        int select;

        while (true) // 유효한 선택이 들어올 때까지 반복
        {
            cout << "1. 적에게 공격을 가한다.\n";
            cout << "2. 기술을 사용한다.\n";
            cout << "3. 가방을 연다.\n";
            cout << "4. 도주를 시도한다.\n";
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
                    cout << "당신은 " << monster->getName() << "에게 " << damage << "의 피해를 입혔다.\n";
                    break;
                }

                case 2: // 스킬
                {
                    // 목록 출력
                    cout << "=== 기술 선택 ===\n";
                    for (int i = 1; i <= 2; i++)
                    {
                        SkillData sd = player->getSkillData(i);
                        cout << i << ". [" << sd.name << "]";
                        if (sd.isPassive)
                        {
                            cout << "(패시브)";
                        }
                        cout << " - " << sd.description << "\n";
                    }

                    cout << "0. 돌아가기\n";
                    cout << "선택 : ";

                    int skillSelect;
                    cin >> skillSelect;
                    if (skillSelect == 0)
                    {
                        continue; // 돌아가기
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
                        {
                            isInvincible = true;
                        }

                        if (sd.cooltime > 0)
                        {
                            skillLastUsed[skillSelect] = turn_cycle;
                        }
                    }
                    else
                    {
                        cout << "올바른 행동이 아니다. 다시 한번 생각해보자.\n";
                        continue;
                    }
                    break;
                }


                case 3: // 아이템
                {
                    // TODO: 아이템 사용 구현 예정
                    break;
                }

                case 4: // 도주
                {
                    cout << "당신은 도주를 시도했다.\n";

                    // SAN 비례 탈출 확률: 최소 30%(SAN=0) ~ 최대 100%(SAN=100)
                    int  escapeChance = 30 + static_cast<int>((player->getSan() / 100.0) * 70);
                    int  randomCall = rand() % 100 + 1;
                    bool escaped = (randomCall <= escapeChance);

                    if (player->getSan() > 80)
                    {
                        if (escaped)
                        {
                            cout << "당신은 침착하게 어둠속에 몸을 숨기고 후퇴하였다.\n";
                        }

                        else
                        {
                            cout << "당신은 침착하게 어둠속에 몸을 숨기고 후퇴하려 했으나 " << monster->getName() << "에게 들켜 실패하였다.\n";
                        }

                    }
                    else if (player->getSan() > 50)
                    {
                        if (escaped)
                        {
                            cout << "당신은 떨리는 몸을 부여잡고 달려서 간신히 도주하였다.\n";
                        }

                        else
                        {
                            cout << "당신은 떨리는 몸을 부여잡고 달려서 도주하려 했으나 길을 헤메는 사이 " << monster->getName() << "에게 따라잡혔다.\n";
                        }

                    }
                    else if (player->getSan() > 10)
                    {
                        if (escaped)
                        {
                            cout << "당신은 거의 제정신이 아닌 상태로 꼴사납게 도망치는데 성공하였다.\n";
                        }
                        else
                        {
                            cout << "당신은 거의 제정신이 아닌 상태로 도망치려 하였으나 돌부리에 걸려 넘어지고 말았다.\n" << monster->getName() << "(이)가 공포의 냄새를 맡고 당신에게 다가온다.\n";
                        }
                    }
                    else
                    {
                        if (escaped)
                        {
                            cout << "당신은 패닉에 빠져 자신이 어디로 가는지도 모르는체 넘어지고 기어가며 적으로부터 달아나는데 성공했다.\n";
                        }
                        else
                        {
                            cout << "당신은 패닉에 빠져 도망치려 했지만 다리가 꼬여 넘어졌다. 벌벌 떠는 당신을 향해 " << monster->getName() << "(이)가 압도적인 공포와 함께 천천히 다가온다.\n";
                        }
                    }

                    if (escaped)
                    {
                        return; // 전투 종료 (도주 성공)
                    }
                    break; // 도주 실패. 턴 종료
                }

                default:
                {
                    cout << "올바른 행동이 아니다. 다시 한번 생각해보자.\n";
                    continue;
                }                
            }
            break;
        }
        // ── 몬스터 사망 확인
            if (monster->getHp() <= 0)
            {
                cout << monster->getName() << "(이)가 쓰러졌다.\n";
                break;
            }
            
        // ── 몬스터 턴 
        cout << monster->getName() << "의 차례...\n";

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
            if (rand() % 10 >= 3)
            {
                monster->NormalAttack(player);
            }
            else
            {
                monster->SpecialAttack(player);
            }
        }

        turn_cycle++;
    }

    //플레이어 사망 또는 몬스터 사망에 따른 승리 및 패배 출력.

    player->setPower(OriginalAtk);
    player->setDefence(OriginalDef);
    player->setSanDefence(OriginalSanDef);


}
