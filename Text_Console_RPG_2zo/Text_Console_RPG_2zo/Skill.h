#pragma once

#include <string>

enum class SkillID
{
    BERSERK,
    ADRENALINE,

    HELLFIRE,
    MIND_OVERLOAD,

    CLEAR_MIND,
    MIND_STRIKE,

    PLUNDER,
    MIST_WALK,

    SHABBY,
    FRAIL_BODY,

    GAMBLER,
    RUSSIAN_ROULETTE
};

struct SkillData
{
    SkillID id;
    std::string name;
    std::string description;
    bool isPassive;
    int cooltime;
};

class Player;
class Monster;

void TakeDamage(Monster* monster, int damage);
void TakeDamage(Player* player, int damage);

void Skill_Hellfire(Player* player, Monster* monster);
void Skill_MindOverload(Player* player, Monster* monster);
void Skill_MindStrike(Player* player, Monster* monster, int& turn_cycle);
void Skill_MistWalk(Player* player, int& turn_cycle);
void Skill_RussianRoulette(Player* player, Monster* monster);

int Skill_PassiveOnAttack(SkillID id, Player* player, int damage);
int Skill_PassiveOnHit(SkillID id, Player* player, Monster* monster, int damage);
