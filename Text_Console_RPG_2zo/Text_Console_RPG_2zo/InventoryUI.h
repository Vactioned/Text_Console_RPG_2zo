#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Inventory.h"
#include "Player.h"

class InventoryUI
{
private:
    std::string GetItemName(const std::string& name)
    {
        if (name == "체력 포션") return "HP\n포션";
        if (name == "정신력 포션") return "정신력\n포션";
        if (name == "공격력 증가") return "공격력\n증가";
        if (name == "약화 포션") return "약화\n포션";
        if (name == "취약 포션") return "취약\n포션";
        if (name == "최대 체력 포션") return "최대 체력\n포션";
        if (name == "최대 정신력 포션") return "최대 정신력\n포션";

        return "?";
    }

    std::string GetItemDescription(const std::string& name)
    {
        if (name == "체력 포션") return "HP 포션\nHP +50";
        if (name == "정신력 포션") return "SAN 포션\nSAN +50";
        if (name == "공격력 증가") return "공격력 증가\n이번 전투 동안 공력력 +10";
        if (name == "약화 포션") return "약화 포션\n이번 전투 동안 적의 공격력 -20%";
        if (name == "취약 포션") return "취약 포션\n이번 전투 동안 적의 방어력 -20%";
        if (name == "최대 체력 포션") return "최대 체력 포션\n최대 체력 +20";
        if (name == "최대 정신력 포션") return "최대 정신력 포션\n최대 정신력 +20";

        return "";
    }

    // 아이템 슬롯
    void DrawSlots(sf::RenderWindow& window, sf::RectangleShape& slot,
        int capacity, int columns, int padding, int slotSize, int gap)
    {
        for (int i = 0; i < capacity; i++)
        {
            int col = i % columns;
            int row = i / columns;

            float x = static_cast<float>(padding + col * (slotSize + gap));
            float y = static_cast<float>(padding + row * (slotSize + gap));

            slot.setPosition(x, y);
            window.draw(slot);
        }
    }

    // 슬롯 내부 아이템 이름
    template<typename T>
    void DrawItems(sf::RenderWindow& window, Inventory<T>& inventory, sf::Font& font,
        int capacity, int columns, int padding, int slotSize, int gap)
    {
        int index = 0;

        for (const T& item : inventory.GetItems())
        {
            if (index >= capacity)
            {
                break;
            }

            int col = index % columns;
            int row = index / columns;

            float x = static_cast<float>(padding + col * (slotSize + gap));
            float y = static_cast<float>(padding + row * (slotSize + gap));

            sf::Text nameText;
            nameText.setFont(font);
            nameText.setString(GetItemName(item.getName()));
            nameText.setCharacterSize(14);
            nameText.setFillColor(sf::Color::Black);
            nameText.setPosition(x + 6, y + 8);

            window.draw(nameText);

            index++;
        }
    }

    // 툴팁
    template<typename T>
    void DrawTooltip(sf::RenderWindow& window, Inventory<T>& inventory, sf::Font& font,
        int columns, int padding, int slotSize, int gap)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        int localX = mousePos.x - padding;
        int localY = mousePos.y - padding;

        if (localX < 0 || localY < 0)
        {
            return;
        }

        int cellSize = slotSize + gap;

        int tooltipCol = localX / cellSize;
        int tooltipRow = localY / cellSize;

        int inCellX = localX % cellSize;
        int inCellY = localY % cellSize;

        int tooltipIndex = tooltipRow * columns + tooltipCol;

        bool isInsideSlot =
            tooltipCol >= 0 &&
            tooltipCol < columns &&
            inCellX < slotSize &&
            inCellY < slotSize &&
            tooltipIndex >= 0 &&
            tooltipIndex < inventory.getSize();

        if (!isInsideSlot)
        {
            return;
        }

        int currentIndex = 0;

        for (const T& item : inventory.GetItems())
        {
            if (currentIndex == tooltipIndex)
            {
                // 툴팁 박스
                sf::RectangleShape tooltipBox(sf::Vector2f(230, 50));
                tooltipBox.setFillColor(sf::Color(80, 60, 50));
                tooltipBox.setOutlineColor(sf::Color::White);
                tooltipBox.setOutlineThickness(1);
                tooltipBox.setPosition(
                    static_cast<float>(mousePos.x + 10),
                    static_cast<float>(mousePos.y + 10)
                );

                // 툴팁 텍스트
                sf::Text tooltipText;
                tooltipText.setFont(font);
                tooltipText.setString(GetItemDescription(item.getName()));
                tooltipText.setCharacterSize(12);
                tooltipText.setFillColor(sf::Color::White);
                tooltipText.setPosition(
                    static_cast<float>(mousePos.x + 18),
                    static_cast<float>(mousePos.y + 18)
                );

                window.draw(tooltipBox);
                window.draw(tooltipText);

                break;
            }

            currentIndex++;
        }
    }

    // 취소 버튼
    void DrawCancelButton(sf::RenderWindow& window,
        sf::RectangleShape& cancelButton, sf::Text& cancelText)
    {
        window.draw(cancelButton);
        window.draw(cancelText);
    }

    // 골드
    void DrawGold(sf::RenderWindow& window, sf::Font& font, sf::Texture& goldTexture, int width, int height, Player* player)
    {
        // 좌표 설정
        float x = static_cast<float>(width);
        float y = static_cast<float>(height);

        // 골드 슬롯
        sf::RectangleShape goldBox(sf::Vector2f(80, 30));
        goldBox.setFillColor(sf::Color(240, 210, 190));
        goldBox.setOutlineColor(sf::Color::White);
        goldBox.setOutlineThickness(2);
        goldBox.setPosition(static_cast<float>(x), static_cast<float>(y));
        window.draw(goldBox);

        // 골드 이미지 출력
        sf::Sprite goldSprite;
        goldSprite.setTexture(goldTexture);
        goldSprite.setPosition(x + 6, y + 4);

        // 이미지 크기 조절
        sf::Vector2u textureSize = goldTexture.getSize();
        if (textureSize.x > 0 && textureSize.y > 0)
        {
            goldSprite.setScale(22.f / textureSize.x, 22.f / textureSize.y);
        }
        window.draw(goldSprite);

        // 골드 텍스트
        sf::Text nameText;
        nameText.setFont(font);
        nameText.setString(to_string(player->getGold()));
        nameText.setCharacterSize(14);
        nameText.setFillColor(sf::Color::Black);
        nameText.setPosition(x + 40, y + 6);
        window.draw(nameText);
    }

public:
    template<typename T>
    bool Open(Inventory<T>& inventory, Player* player, bool isBattle, Monster* monster = nullptr)
    {
        const int slotSize = 70;
        const int columns = 4;
        const int padding = 8;
        const int gap = 4;

        int capacity = inventory.getCapacity();
        int rows = (capacity + columns - 1) / columns;

        int windowWidth = (padding * 2 + columns * slotSize + (columns - 1) * gap) * 2;
        int windowHeight = (padding * 2 + rows * slotSize + (rows - 1) * gap) * 2;

        // 창 생성
        sf::RenderWindow window(
            sf::VideoMode(windowWidth, windowHeight),
            "Inventory",
            sf::Style::Titlebar
        );
        std::cout << "window 생성 완료\n";

        sf::RectangleShape slot(sf::Vector2f(slotSize, slotSize));
        slot.setFillColor(sf::Color(240, 210, 190));
        slot.setOutlineColor(sf::Color::White);
        slot.setOutlineThickness(2);

        sf::Font font;

        if (!font.loadFromFile("C:/Windows/Fonts/malgun.ttf"))
        {
            std::cout << "InventoryUI Font Load Fail\n";
        }

        sf::Texture goldTexture;
        if (!goldTexture.loadFromFile("Image/Gold.png"))
        {
            std::cout << "Gold Texture Load Fail\n";
        }

        // 취소 버튼
        sf::RectangleShape cancelButton(sf::Vector2f(80, 35));
        cancelButton.setFillColor(sf::Color(90, 70, 60));
        cancelButton.setOutlineColor(sf::Color::White);
        cancelButton.setOutlineThickness(1);
        cancelButton.setPosition(8.f, static_cast<float>(windowHeight - 43));

        // 취소 텍스트
        sf::Text cancelText;
        cancelText.setFont(font);
        cancelText.setString("Cancel");
        cancelText.setCharacterSize(14);
        cancelText.setFillColor(sf::Color::White);
        cancelText.setPosition(25.f, static_cast<float>(windowHeight - 35));

        bool printed = false;
        bool useItem = false;

        while (window.isOpen())
        {
            sf::Event event;

            if (printed == false)
            {
                std::cout << "마우스 우클릭 시 아이템을 삭제 할 수 있습니다.\n전투 중 삭제는 불가능 합니다.\n";
                printed = true;
            }

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::MouseButtonPressed &&
                    event.mouseButton.button == sf::Mouse::Left)
                {
                    int mouseX = event.mouseButton.x;
                    int mouseY = event.mouseButton.y;

                    int col = (mouseX - padding) / (slotSize + gap);
                    int row = (mouseY - padding) / (slotSize + gap);

                    int index = row * columns + col;

                    // 취소 버튼 클릭 시 창 닫기
                    if (cancelButton.getGlobalBounds().contains(
                        static_cast<float>(mouseX),
                        static_cast<float>(mouseY)))
                    {
                        window.close();
                        break;
                    }

                    if (index >= 0 && index < inventory.getSize())
                    {
                        int currentIndex = 0;
                        int removeIndex = -1;

                        for (const T& item : inventory.GetItems())
                        {
                            if (currentIndex == index)
                            {
                                // 비 전투 시 사용 불가 항목
                                bool onlyBattleItem =
                                    item.getName() == "공격력 증가" ||
                                    item.getName() == "취약 포션" ||
                                    item.getName() == "약화 포션";

                                if (!isBattle && onlyBattleItem)
                                {
                                    std::cout << "전투 중에만 사용할 수 있는 아이템입니다.\n";
                                    break;
                                }

                                // 아이템 사용
                                if (isBattle && monster != nullptr)
                                {
                                    item.use(player, monster);
                                }
                                else
                                {
                                    item.use(player);
                                }
                                removeIndex = index;
                                window.close();
                                useItem = true;
                                break;
                            }

                            currentIndex++;
                        }

                        if (removeIndex != -1)
                        {
                            inventory.RemoveItem(removeIndex);
                        }
                    }
                }

                // 우클릭 시 아이템 삭제
                if (event.type == sf::Event::MouseButtonPressed &&
                    event.mouseButton.button == sf::Mouse::Right)
                {
                    if (isBattle)
                    {
                        std::cout << "전투 중에는 아이템을 버릴 수 없습니다.\n";
                        continue;
                    }

                    int mouseX = event.mouseButton.x;
                    int mouseY = event.mouseButton.y;

                    int col = (mouseX - padding) / (slotSize + gap);
                    int row = (mouseY - padding) / (slotSize + gap);

                    int index = row * columns + col;

                    if (index >= 0 && index < inventory.getSize())
                    {
                        inventory.RemoveItem(index);
                        std::cout << "\n아이템을 버렸습니다.\n";
                        inventory.PrintAllItems();
                    }
                }
            }

            window.clear(sf::Color(210, 170, 145));

            DrawSlots(window, slot, capacity, columns, padding, slotSize, gap);
            DrawItems(window, inventory, font, capacity, columns, padding, slotSize, gap);
            DrawTooltip(window, inventory, font, columns, padding, slotSize, gap);
            DrawCancelButton(window, cancelButton, cancelText);
            DrawGold(window, font, goldTexture, windowWidth - 90, windowHeight - 40, player);

            window.display();
        }

        return useItem;
    }
};
