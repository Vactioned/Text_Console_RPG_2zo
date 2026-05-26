#include "LogManager.h"
#include "Player.h"
#include "thread"       // 컴퓨터를 잠깐 지연시키기 위한 라이브러리
#include "chrono"       // 시간 단위를 쓰기 위한 라이브러리

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

void LogManager::TypePrint(const string& message, int delayMs)
{
    // 문자열의 처음부터 끝까지 한 글자(char)씩 돌면서 출력
    for (char c : message)
    {
        cout << c << flush;     // flush를 해줘야 모았다가 한 번에 출력하지 않고 한 번에 한 글자씩 출력함

        // 컴퓨터가 지정한 밀리초(ms)만큼 잠깐 멈춘다.
        this_thread::sleep_for(chrono::milliseconds(delayMs));
    }
    cout << endl;   
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
