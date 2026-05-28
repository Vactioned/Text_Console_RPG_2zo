#include "Item.h"
#include "Player.h"
#include "Monster.h"

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <vector>

using namespace std;

// 생성자
Item::Item() : name(""), type(ItemType::HealPotion), value(0)
{
}

Item::Item(const string& name, ItemType type, int value)
    : name(name), type(type), value(value)
{
}

// getter
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

// 아이템 정보 출력
void Item::PrintInfo() const
{
    switch (type)
    {
    case ItemType::HealPotion:
        cout << name << " | 체력 +" << value << '\n';
        break;

    case ItemType::SanPotion:
        cout << name << " | 정신력 +" << value << '\n';
        break;

    case ItemType::AttackBoost:
        cout << name << " | 공격력 +" << value << " (이번 전투 동안)\n";
        break;

    case ItemType::WeaknessPotion:
        cout << name << " | 이번 전투 동안 적 공격력 " << value << "% 감소\n";
        break;

    case ItemType::VulnerabilityPotion:
        cout << name << " | 이번 전투 동안 적 방어력 " << value << "% 감소\n";
        break;

    case ItemType::MaxHpPotion:
        cout << name << " | 최대 체력 +" << value << '\n';
        break;

    case ItemType::MaxSanPotion:
        cout << name << " | 최대 정신력 +" << value << '\n';
        break;

    default:
        cout << "알 수 없는 아이템\n";
        break;
    }
}

// 아이템 사용
void Item::use(Player* player) const
{
    if (player == nullptr)
    {
        cout << "[오류] Player가 존재하지 않습니다.\n";
        return;
    }

    int beforeValue = 0;
    int afterValue = 0;

    switch (type)
    {
    case ItemType::HealPotion:
        beforeValue = player->getHp();
        afterValue = min(beforeValue + value, player->getMaxHp());
        player->setHp(afterValue);
        cout << "[아이템 사용] " << name << " | 체력 회복: " << beforeValue << " -> " << afterValue << '\n';
        break;

    case ItemType::SanPotion:
        beforeValue = player->getSan();
        afterValue = min(beforeValue + value, player->getMaxSan());
        player->setSan(afterValue);
        cout << "[아이템 사용] " << name << " | 정신력 회복: " << beforeValue << " -> " << afterValue << '\n';
        break;

    case ItemType::AttackBoost:
        beforeValue = player->getPower();
        afterValue = beforeValue + value;
        player->setPower(afterValue);
        cout << "[아이템 사용] " << name << " | 공격력 증가: " << beforeValue << " -> " << afterValue << '\n';
        break;

    case ItemType::WeaknessPotion:
        cout << "[아이템 사용] " << name << " | 전투 중에만 사용할 수 있습니다.\n";
        break;

    case ItemType::VulnerabilityPotion:
        cout << "[아이템 사용] " << name << " | 전투 중에만 사용할 수 있습니다.\n";
        break;

    case ItemType::MaxHpPotion:
        beforeValue = player->getMaxHp();
        afterValue = beforeValue + value;
        player->setMaxHp(afterValue);
        player->setHp(min(player->getHp() + value, player->getMaxHp()));
        cout << "[아이템 사용] " << name << " | 최대 체력 증가: " << beforeValue << " -> " << afterValue << '\n';
        break;

    case ItemType::MaxSanPotion:
        beforeValue = player->getMaxSan();
        afterValue = beforeValue + value;
        player->setMaxSan(afterValue);
        player->setSan(min(player->getSan() + value, player->getMaxSan()));
        cout << "[아이템 사용] " << name << " | 최대 정신력 증가: " << beforeValue << " -> " << afterValue << '\n';
        break;

    default:
        cout << "[오류] 정의되지 않은 ItemType\n";
        break;
    }
}

// 전투 중 아이템 사용
void Item::use(Player* player, Monster* monster) const
{
    if (player == nullptr)
    {
        cout << "[오류] Player가 존재하지 않습니다.\n";
        return;
    }

    if (monster == nullptr)
    {
        cout << "[오류] Monster가 존재하지 않습니다.\n";
        return;
    }

    int beforeValue = 0;
    int afterValue = 0;

    switch (type)
    {
    case ItemType::WeaknessPotion:
        beforeValue = monster->getAttackPower();
        afterValue = beforeValue - beforeValue * value / 100;
        monster->setAttackPower(afterValue);
        cout << "[아이템 사용] " << name << " | 적 공격력 감소: " << beforeValue << " -> " << afterValue << '\n';
        break;

    case ItemType::VulnerabilityPotion:
        beforeValue = monster->getDefence();
        afterValue = beforeValue - beforeValue * value / 100;
        monster->setDefence(afterValue);
        cout << "[아이템 사용] " << name << " | 적 방어력 감소: " << beforeValue << " -> " << afterValue << '\n';
        break;

    default:
        use(player);
        break;
    }
}

// 아이템 생성 함수
Item Item::CreateHealPotion(int playerLevel)
{
    int healValue = 50 + (playerLevel / 10) * 100;
    return Item("체력 포션", ItemType::HealPotion, healValue);
}

Item Item::CreateSanPotion()
{
    return Item("정신력 포션", ItemType::SanPotion, 50);
}

Item Item::CreateAttackBoost()
{
    return Item("공격력 증가", ItemType::AttackBoost, 10);
}

Item Item::CreateWeaknessPotion()
{
    return Item("약화 포션", ItemType::WeaknessPotion, 20);
}

Item Item::CreateVulnerabilityPotion()
{
    return Item("취약 포션", ItemType::VulnerabilityPotion, 20);
}

Item Item::CreateMaxHpPotion()
{
    return Item("최대 체력 포션", ItemType::MaxHpPotion, 20);
}

Item Item::CreateMaxSanPotion()
{
    return Item("최대 정신력 포션", ItemType::MaxSanPotion, 15);
}

// 챕터 클리어 보상
vector<Item> Item::CreateChapterClearReward()
{
    vector<Item> rewards;

    rewards.push_back(CreateAttackBoost());
    rewards.push_back(CreateWeaknessPotion());
    rewards.push_back(CreateVulnerabilityPotion());

    if (rand() % 2 == 0)
    {
        rewards.push_back(CreateMaxHpPotion());
    }
    else
    {
        rewards.push_back(CreateMaxSanPotion());
    }

    return rewards;
}