#include "Item.h"
#include "Player.h"

#include <iostream>
#include <algorithm>
#include <cstdlib>

using namespace std;

// 생성자
Item::Item()
    : name(""), type(ItemType::HealPotion), value(0)
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
        cout << name << " | 이번 전투 동안 적이 받는 데미지 " << value << "% 증가\n";
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
        cout << "[아이템 사용] " << name << " | 적 공격력 감소 효과 적용\n";
        break;

    case ItemType::VulnerabilityPotion:
        cout << "[아이템 사용] " << name << " | 적 취약 효과 적용\n";
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

// 아이템 생성 함수
Item Item::CreateHealPotion()
{
    return Item("체력 포션", ItemType::HealPotion, 50);
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

// 일반 전투 보상 (30% 확률, 체력/정신력 포션)
bool Item::CreateBattleReward(Item& reward)
{
    int chance = rand() % 100;

    if (chance >= 30)
    {
        return false;
    }

    int potionType = rand() % 2;

    if (potionType == 0)
    {
        reward = CreateHealPotion();
    }
    else
    {
        reward = CreateSanPotion();
    }

    return true;
}

// 챕터 클리어 보상 (5개 중 랜덤 지급)
Item Item::CreateChapterClearReward()
{
    int rewardType = rand() % 5;

    switch (rewardType)
    {
    case 0:
        return CreateAttackBoost();

    case 1:
        return CreateWeaknessPotion();

    case 2:
        return CreateVulnerabilityPotion();

    case 3:
        return CreateMaxHpPotion();

    case 4:
        return CreateMaxSanPotion();

    default:
        return CreateAttackBoost();
    }
}
