#pragma once
#include "InventoryUI.h"
#include <string>

class LogManager
{
public:
    // 화면을 깔끔하게 지우는 함수
    static void Clear();

    // 엔터 대기 함수
    static void PressEnter();

    // 메인 메뉴 함수     
    static void MainMenu(Player& player, Inventory<Item>& inventory);   // 매개 변수를 받도록 수정

    // 타이핑 효과 함수
    // delayMs: 글자 사이의 간격 (밀리초 단위)
    static void TypePrint(const std::string& message, int delayMs = 15);

    static void CH1();

    static void CH1_Boss();

    static string InputPlayerName();

    static string SelectJob();
};
