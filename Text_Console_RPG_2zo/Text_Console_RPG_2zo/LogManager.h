#pragma once
#include <string>

class LogManager
{
public:
    // 화면을 깔끔하게 지우는 함수
    static void Clear();

    // 엔터 대기 함수
    static void PressEnter();

    // 메인 메뉴 함수     
    static void MainMenu(Player& player);   // 매개 변수를 받도록 수정
};
