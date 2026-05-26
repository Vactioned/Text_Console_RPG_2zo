#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include "Inventory.h"
#include "Item.h"
#include "Player.h"

class InventoryUI
{
private:
    std::string GetItemName(const std::string& name)
    {
        if (name == "체력 포션") return "HP\nPotion";
        if (name == "정신력 포션") return "SAN\nPotion";
        if (name == "공격력 증가") return "ATK\nIncrease";
        if (name == "약화 포션") return "Weak\nPotion";
        if (name == "취약 포션") return "Damage\nIncrease";

        return "?";
    }

    std::string GetItemDescription(const std::string& name)
    {
        if (name == "체력 포션") return "Recovers 50 HP.";
        if (name == "정신력 포션") return "Recovers 50 SAN.";
        if (name == "공격력 증가") return "Attack increases by 10 during this battle.";
        if (name == "약화 포션") return "Reduces the enemy's attack power by 30% for 3 turns.";
        if (name == "취약 포션") return "Damage dealt to enemies increases by 30% for 3 turns.";

        return "";
    }

public:
    template<typename T>
    void Open(Inventory<T>& inventory, Player* player, bool isBattle)
    {
        // 아이템 칸 픽셀 크기
        const int slotSize = 70;
        // 가로 줄 수
        const int columns = 4;
        // 창의 가장자리와 슬롯 사이의 여백 픽셀
        const int padding = 8;
        // 칸과 칸 사이 여백 픽셀
        const int gap = 4;

        int capacity = inventory.getCapacity();
        // 세로 줄 수
        int rows = (capacity + columns - 1) / columns;

        // 새롭게 띄우는 윈도우 창 크기
        int windowWidth = (padding * 2 + columns * slotSize + (columns - 1) * gap) * 2;
        int windowHeight = (padding * 2 + rows * slotSize + (rows - 1) * gap) * 2;

        // 윈도우 창 생성
        sf::RenderWindow window(
            sf::VideoMode(windowWidth, windowHeight),
            "Inventory"
        );

        // 아이템 칸 모양 설정 cf) 다각형을 하고싶으면 sf::CircleShape hexagon(30, 6); -> 정확한 뜻은 6개의 점을 가진 도형
        // sf::CircleShape hexagon(30, 4);를 하면 마름모가 나옴 이거로 사각형을 만들고 싶다면 square.setRotation(45);를 추가해서 회전해줘야함
        sf::RectangleShape slot(sf::Vector2f(slotSize, slotSize));
        // 슬롯의 색, 외곽선 색, 외곽선 두께
        slot.setFillColor(sf::Color(240, 210, 190));
        slot.setOutlineColor(sf::Color::White);
        slot.setOutlineThickness(2);

        // 폰트 클래스 객체 생성자
        sf::Font font;

        // 폰트 설정 C++의 버전에 따라 사용할 수 있는 폰트가 달라짐
        if (!font.loadFromFile("C:/Windows/Fonts/malgun.ttf"))
        {
            std::cout << "InventoryUI Font Load Fail\n";
        }

        bool printed = false;

        // 창이 열려있는동안 반복
        while (window.isOpen())
        {
            sf::Event event;

            if (printed == false)
            {
                std::cout << "마우스 우클릭 시 아이템을 삭제 할 수 있습니다.\n전투 중 삭제는 불가능 합니다.\n";
                printed = true;
            }

            // 이벤트가 발생하면 반복문 실행 / pollEvent가 bool타입을 반환하기 때문에 break가 없어도 무한루프는 발생하지 않음
            while (window.pollEvent(event))
            {
                // 창의 X키에 입력이 들어갔을 때
                if (event.type == sf::Event::Closed)
                    window.close();

                // and 조건문 키입력 발생 and 그 키가 esc인 경우
                if (event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::Escape)
                    window.close();

                // and 조건문 마우스 입력 발생 and 그 입력이 좌클릭인 경우
                if (event.type == sf::Event::MouseButtonPressed &&
                    event.mouseButton.button == sf::Mouse::Left)
                {
                    // 입력이 발생 된 지점의 좌표를 변수로 저장
                    int mouseX = event.mouseButton.x;
                    int mouseY = event.mouseButton.y;

                    // ex) mouseX = 70, padding = 8, slotSize = 48, gap = 4  ->  62 / 52
                    // 정수타입이기 때문에 해당 값은 1
                    int col = (mouseX - padding) / (slotSize + gap);
                    int row = (mouseY - padding) / (slotSize + gap);

                    // row 몇 번째 행, col 몇 번째 열, columns 열의 총 갯수 cf) 행열 0부터 시작
                    int index = row * columns + col;

                    if (index >= 0 && index < inventory.getSize())
                    {
                        int currentIndex = 0;
                        int removeIndex = -1;

                        // 모든 아이템을 불러올 때 까지 반복
                        // 하지만 아래의 if문에 break를 걸어둬서 탈출 가능
                        for (const T& item : inventory.GetItems())
                        {
                            // 클릭한 인벤토리칸과 현재 검사하는 인벤토리칸이 일치하면 실행되는 조건문
                            if (currentIndex == index)
                            {
                                std::cout << "\n[사용 전]\n";
                                std::cout << "HP  : " << player->getHp() << " / " << player->getMaxHp() << '\n';
                                std::cout << "SAN : " << player->getSan() << " / " << player->getMaxSan() << '\n';
                                std::cout << "ATK : " << player->getPower() << '\n' << '\n';

                                item.use(player);

                                std::cout << "\n[사용 후]\n";
                                std::cout << "HP  : " << player->getHp() << " / " << player->getMaxHp() << '\n';
                                std::cout << "SAN : " << player->getSan() << " / " << player->getMaxSan() << '\n';
                                std::cout << "ATK : " << player->getPower() << '\n';
                                removeIndex = index;
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

            // 배경 색 채우기
            // clear로 창을 갈아엎는다고 생각
            window.clear(sf::Color(210, 170, 145));

            for (int i = 0; i < capacity; i++)
            {
                // 나머지가 열 번호, 몫이 행 번호
                int col = i % columns;
                int row = i / columns;

                // 좌표 계산, static_cast<타입>은 원하는 타입으료 변환시켜주는 c++ 문법
                // 좌표에는 float이 들어가야하기때문에 타입을 변경한 것
                float x = static_cast<float>(padding + col * (slotSize + gap));
                float y = static_cast<float>(padding + row * (slotSize + gap));

                // 해당 좌표에 슬롯을 생성
                slot.setPosition(x, y);
                // 생성된 슬롯을 그리기
                window.draw(slot);
            }

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

            // 마우스 오버 시 툴팁 생성
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            int localX = mousePos.x - padding;
            int localY = mousePos.y - padding;

            if (localX >= 0 && localY >= 0)
            {
                int cellSize = slotSize + gap;

                int tooltipcol = localX / cellSize;
                int tooltiprow = localY / cellSize;

                int inCellX = localX % cellSize;
                int inCellY = localY % cellSize;

                int tooltipindex = tooltiprow * columns + tooltipcol;

                bool isInsideSlot =
                    tooltipcol >= 0 &&
                    tooltipcol < columns &&
                    inCellX < slotSize &&
                    inCellY < slotSize &&
                    tooltipindex >= 0 &&
                    tooltipindex < inventory.getSize();

                if (isInsideSlot)
                {
                    int cIndex = 0;

                    for (const T& item : inventory.GetItems())
                    {
                        if (cIndex == tooltipindex)
                        {
                            sf::RectangleShape tooltipBox(sf::Vector2f(300, 100));
                            tooltipBox.setFillColor(sf::Color(80, 60, 50));
                            tooltipBox.setOutlineColor(sf::Color::White);
                            tooltipBox.setOutlineThickness(1);
                            tooltipBox.setPosition(static_cast<float>(mousePos.x + 10), static_cast<float>(mousePos.y + 10));

                            sf::Text tooltipText;
                            tooltipText.setFont(font);
                            tooltipText.setString(GetItemName(item.getName()) + "\n" + GetItemDescription(item.getName()));
                            tooltipText.setCharacterSize(12);
                            tooltipText.setFillColor(sf::Color::White);
                            tooltipText.setPosition(static_cast<float>(mousePos.x + 18), static_cast<float>(mousePos.y + 18));

                            window.draw(tooltipBox);
                            window.draw(tooltipText);

                            break;
                        }

                        cIndex++;
                    }
                }
            }

            // 앞서 draw로 만든 창들을 보여주기
            // 혹시 display가 앞에 있으면 그리는 과정이 보이는지 의문이 들었지만 아님 그냥 빈 창만 보일 뿐
            // draw마다 display를 하면 과정이 보일 수 있겠지만 코드 진행이 빨라서 못 볼 가능성이 큼
            window.display();
        }
    }
};
