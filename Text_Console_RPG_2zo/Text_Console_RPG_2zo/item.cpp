#include "Item.h"
#include "Player.h"

#include <iostream>
#include <algorithm>

using namespace std;

Item::Item(const string& name, ItemType type, int value)
    : name(name), type(type), value(value)
{
}

string Item::getName() const
{
    return name;
}

ItemType Item::getType() const
{
    return type;
}

int Item::getValue() const
{
    return value;
}

//  Null 체크
void Item::use(Player* player) const
{
    
    if (player == nullptr)
    {
        cout << "[오류] 아이템을 사용할 대상(Player)이 존재하지 않습니다." << '\n';
        return;
    }

    int beforeValue = 0;
    int afterValue = 0;

    switch (type)
    {
    case ItemType::HealPotion:
        beforeValue = player->getHP(); 
        afterValue = min(beforeValue + value, player->getmaxHP());
        player->setHP(afterValue);
        cout << "[아이템 사용] " << name << " | 체력 회복: " << beforeValue << " -> " << afterValue << '\n';
        break;

    case ItemType::SANPotion:
        beforeValue = player->getSAN();
        afterValue = min(beforeValue + value, player->getmaxSAN());
        player->setSAN(afterValue);
        cout << "[아이템 사용] " << name << " | 정신력 회복: " << beforeValue << " -> " << afterValue << '\n';
        break;

    case ItemType::AttackBoost:
        beforeValue = player->getPower();
        afterValue = beforeValue + value;
        player->setPower(afterValue);
        cout << "[아이템 사용] " << name << " | 공격력 증가: " << beforeValue << " -> " << afterValue << " (이번 전투 동안 적용)" << '\n';
        break;

    default:
        cout << "[오류] 정의되지 않은 ItemType 입니다." << '\n';
        break;
    }
}

Item Item::createHealPotion()
{
    return Item("체력 포션", ItemType::HealPotion, 50);
}

Item Item::createSANPotion()
{
    return Item("정신력 포션", ItemType::SANPotion, 50);
}

Item Item::createAttackBoost()
{
    return Item("공격력 증가", ItemType::AttackBoost, 10);
}
