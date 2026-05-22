#pragma once

#include <string>

class Player;

enum class ItemType
{
    HealPotion,
    SANPotion,
    AttackBoost
};

class Item
{
private:
    std::string name;
    ItemType type;
    int value;

public:
    Item(const std::string& name, ItemType type, int value);

    std::string getName() const;
    ItemType getType() const;
    int getValue() const;

    // Player& 대신 Player* 를 받도록 수정 
    void use(Player* player) const;

    static Item createHealPotion();
    static Item createSANPotion();
    static Item createAttackBoost();
};
