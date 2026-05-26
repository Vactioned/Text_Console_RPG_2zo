#include "Item.h"
#include "Player.h"

#include <iostream>
#include <algorithm>

using namespace std;

Item::Item(const string& name, ItemType type, int value)
    : name(name), type(type), value(value)
{
}

// getter
string Item::getName() const { return name; }
ItemType Item::getType() const { return type; }
int Item::getValue() const { return value; }

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
        cout << name << " | 공격력 +" << value << " (이번 전투 동안)" << '\n';
        break;

    case ItemType::WeaknessPotion:
        cout << name << " | 3턴 동안 적 공격력 " << value << "% 감소" << '\n';
        break;

    case ItemType::VulnerabilityPotion:
        cout << name << " | 3턴 동안 적이 받는 데미지 " << value << "% 증가" << '\n';
        break;

    default:
        cout << "알 수 없는 아이템" << '\n';
        break;
    }
}

// 아이템 사용
void Item::Use(Player* player) const
{
    if (player == nullptr)
    {
        cout << "[오류] 아이템을 사용할 대상(Player)이 존재하지 않습니다." << '\n';
        return;
    }

    int beforevalue = 0;
    int aftervalue = 0;

    switch (type)
    {
    case ItemType::HealPotion:
        beforevalue = player->getHp();
        aftervalue = min(beforevalue + value, player->getMaxHp());
        player->setHp(aftervalue);
        cout << "[아이템 사용] " << name << " | 체력 회복: " << beforevalue << " -> " << aftervalue << '\n';
        break;

    case ItemType::SanPotion:
        beforevalue = player->getSan();
        aftervalue = min(beforevalue + value, player->getMaxSan());
        player->setSan(aftervalue);
        cout << "[아이템 사용] " << name << " | 정신력 회복: " << beforevalue << " -> " << aftervalue << '\n';
        break;

    case ItemType::AttackBoost:
        beforevalue = player->getPower();
        aftervalue = beforevalue + value;
        player->setPower(aftervalue);
        cout << "[아이템 사용] " << name << " | 공격력 증가: " << beforevalue << " -> " << aftervalue << " (이번 전투 동안 적용)" << '\n';
        break;
            
    case ItemType::WeaknessPotion:
        cout << "[아이템 사용] " << name << " | 3턴 동안 적 공격력 " << value << "% 감소" << '\n';
        break;

    case ItemType::VulnerabilityPotion:
        cout << "[아이템 사용] " << name << " | 3턴 동안 적이 받는 데미지 " << value << "% 증가" << '\n';
        break;

    default:
        cout << "[오류] 정의되지 않은 ItemType 입니다." << '\n';
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
    return Item("공격력 증가 포션", ItemType::AttackBoost, 10);
}

Item Item::CreateWeaknessPotion()
{
    return Item("약화 포션", ItemType::WeaknessPotion, 30);
}

Item Item::CreateVulnerabilityPotion()
{
    return Item("취약 포션", ItemType::VulnerabilityPotion, 30);
}
