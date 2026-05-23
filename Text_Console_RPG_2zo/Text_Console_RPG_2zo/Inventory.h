#pragma once
#include <list>
#include <iostream>
#include "Item.h"

template<typename T>
class Inventory
{
private:
    std::list<T> items_;
    int capacity_;

public:
    Inventory(int capacity)
        : capacity_(capacity)
    {
    }

    int getSize()
    {
        return items_.size();
    }

    // 리스트에서는 보통 size 설정할 일 없다곤 하는데 일단 만들어뒀습니다.
    void setSize(int size)
    {
    }

    int getCapacity() const
    {
        return capacity_;
    }

    void setCapacity(int capacity)
    {
        capacity_ = capacity;
    }

    const std::list<T>& GetItems() const
    {
        return items_;
    }

    void AddItem(T item)
    {
        if (items_.size() >= capacity_)
        {
            std::cout << "인벤토리가 가득 찼습니다.\n";
            return;
        }

        items_.push_back(item);
    }

    void RemoveItem(int index)
    {
        if (index < 1 || index > items_.size())
        {
            std::cout << "잘못된 번호입니다.\n";
            return;
        }

        auto it = items_.begin();

        for (int i = 1; i < index; i++)
        {
            ++it;
        }

        items_.erase(it);

        std::cout << "아이템을 제거했습니다.\n";
    }

    // item쪽에서 PrintInfo 작성안하면 내가 직접 작성해야함 조정 필요
    void PrintAllItems()
    {
        std::cout << "\n[ Inventory (" << items_.size() << "/" << capacity_ << ") ]\n";

        int index = 1;
        for (T& item : items_)
        {
            std::cout << index << ". ";
            // item.PrintInfo();
            std::cout << item.getName() << "\n";
            index++;
        }
    }

    // 규칙 논의
    void Resize(int newCap)
    {
        capacity_ = newCap;

        while (items_.size() > capacity_)
        {
            items_.pop_back();
        }
    }

    void SortByPrice()
    {
        items_.sort([](const Item& a, const Item& b)
            {
                return a.price < b.price;
            });
    }
};
