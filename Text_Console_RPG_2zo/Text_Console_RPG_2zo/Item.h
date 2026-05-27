#pragma once

#include <string>

using namespace std;

class Player;

// 아이템 종류
enum class ItemType
{
    HealPotion,          // 체력 회복 포션
    SanPotion,           // 정신력 회복 포션    
    AttackBoost,         // 공격력 증가 (이번 전투만)     

    WeaknessPotion,      // 적의 공격력 감소             (미구현)
    VulnerabilityPotion, // 적에게 가하는 피해 증가       (미구현)

    MaxHpPotion,         // 최대 체력 영구 증가
    MaxSanPotion         // 최대 정신력 영구 증가
};

class Item
{
private:
    string name;
    ItemType type;
    int value;

public:
    // 생성자
    Item(const string& name, ItemType type, int value);

    // getter
    string getName() const;
    ItemType getType() const;
    int getValue() const;

    // 아이템 정보 출력
    void PrintInfo() const;

    // 아이템 사용
    void use(Player* player) const;

    // 아이템 생성 함수
    static Item CreateHealPotion();
    static Item CreateSanPotion();
    static Item CreateAttackBoost();
    static Item CreateWeaknessPotion();
    static Item CreateVulnerabilityPotion();

    // 영구 증가 포션
    static Item CreateMaxHpPotion();
    static Item CreateMaxSanPotion();
};