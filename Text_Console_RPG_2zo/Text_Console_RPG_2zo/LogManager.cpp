#include "LogManager.h"
#include <iostream>

void LogManager::Clear()
{
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
}

void LogManager::PressEnter()
{
        std::cout << "\n[ 엔터(Enter)를 누르면 계속합니다... ]";
        std::cin.get(); // 사용자가 엔터를 누를 때까지 대기
}
