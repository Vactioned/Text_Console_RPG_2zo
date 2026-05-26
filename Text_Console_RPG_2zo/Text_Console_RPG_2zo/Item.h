#pragma once

#include <string>

class Player;

enum class ItemType
{
    HealPotion,
    SanPotion,
    AttackBoost,
    WeaknessPotion,
    VulnerabilityPotion
};

class Item
{
private:
    std::string name;
    ItemType type;
    int value;

public:
    Item(const std::string& name, ItemType type, int value);

    // getter
    std::string getName() const;
    ItemType getType() const;
    int getValue() const;

    // 아이템 사용
    void Use(Player* player) const;

    // 아이템 생성 함수
    static Item CreateHealPotion();
    static Item CreateSanPotion();
    static Item CreateAttackBoost();
    static Item CreateWeaknessPotion();
    static Item CreateVulnerabilityPotion();
};
