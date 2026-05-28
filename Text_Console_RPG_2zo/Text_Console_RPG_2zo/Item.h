#pragma once

#include <string>
#include <vector>

using namespace std;

class Player;
class Monster;

enum class ItemType
{
    HealPotion,          // 체력 회복 포션
    SanPotion,           // 정신력 회복 포션
    AttackBoost,         // 공격력 증가 포션
    WeaknessPotion,      // 약화 포션
    VulnerabilityPotion, // 취약 포션
    MaxHpPotion,         // 최대 체력 증가 포션
    MaxSanPotion         // 최대 정신력 증가 포션
};

class Item
{
private:
    string name;
    ItemType type;
    int value;

public:
    Item();
    Item(const string& name, ItemType type, int value);

    string getName() const;
    ItemType getType() const;
    int getValue() const;

    void PrintInfo() const;

    // 일반 아이템 사용
    void use(Player* player) const;

    // 전투 중 아이템 사용
    void use(Player* player, Monster* monster) const;

    // 아이템 생성 함수
    static Item CreateHealPotion();
    static Item CreateSanPotion();
    static Item CreateAttackBoost();
    static Item CreateWeaknessPotion();
    static Item CreateVulnerabilityPotion();
    static Item CreateMaxHpPotion();
    static Item CreateMaxSanPotion();

    // 챕터 클리어 보상
    static vector<Item> CreateChapterClearReward();
};