#include "LogManager.h"
#include "Player.h"

#include <iostream>

using namespace std;

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

void LogManager::MainMenu(Player& player)
{
    int select;
    bool isGameStart = true;    // 현재 게임이 진행 중인지 판단

    while (isGameStart)
    {
        cout << "================================================================" << endl;
        cout << "                       당신은 무엇을 할까                         " << endl;
        cout << "================================================================" << endl;
        cout << "   1. 의뢰 수행" << endl;
        cout << "   2. 상태 확인" << endl;
        cout << "   3. 가방 확인" << endl;
        cout << "   4. 게임 종료" << endl;
        cout << "================================================================" << endl;
        cin >> select;

        switch (select)
        {
        case 1:
            // 전투 시스템 호출 예정 (추후에 임무를 선택할 수 있도록 하면 좋을듯)
            break;
        case 2:
            player.printPlayerStatus();
            PressEnter();
            break;
        case 3:
            // 인벤토리 확인 함수 호출 예정
            PressEnter();
            break;
        case 4:
            isGameStart = false;
            break;
        default:
            cout << "   잘못된 선택입니다. 다시 선택해주세요." << endl;
            break;
        }
    }
}
