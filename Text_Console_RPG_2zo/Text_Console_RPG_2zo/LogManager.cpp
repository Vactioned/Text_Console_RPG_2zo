#include "LogManager.h"
#include "Player.h"
#include <thread>       // 컴퓨터를 잠깐 지연시키기 위한 라이브러리
#include <chrono>       // 시간 단위를 쓰기 위한 라이브러리
#include <fstream>      // .txt 파일을 업로드 하기 위해 필요한 라이브러리
#include <windows.h>    // 색 변경을 위해 필요한 라이브러리

#include <iostream>

using namespace std;

void SetColor(int colorCode)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCode);
}

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
    for (size_t i = 0; i < message.length(); ++i)
    {
        // 만약 '&' 기호를 만나고, 그 뒤에 숫자가 더 있다면 (색상 코드 파싱)
        if (message[i] == '&' && i + 1 < message.length() && isdigit(message[i + 1]))
        {
            int color = message[i + 1] - '0'; // 문자를 숫자로 변경 (0~9번 색상)

            // 만약 두 자리 수 색상(10~14)까지 지원하고 싶다면 추가 처리가 필요하지만,
            // 간단하게 한 자리 수(0~9)만 쓸 때는 이렇게 처리합니다.
            // 더 정교하게 하려면 &14처럼 뒤에 두 자리를 읽게 만들면 됩니다.

            SetColor(color);
            i++; // 숫자 부분은 출력하지 않고 건너뜁니다.
            continue;
        }

        cout << message[i] << flush;
        this_thread::sleep_for(chrono::milliseconds(delayMs));
    }
    cout << endl;
    SetColor(7); // 한 줄 출력이 끝나면 안전하게 기본 흰색으로 리셋
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
            player.PrintPlayerStatus();
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

void LogManager::CH1()
{
    ifstream file("CH1.txt");

    if (!file.is_open())
    {
        cout << "파일을 열 수 없습니다.\n";
    }

    string line;
    while (getline(file, line))
    {
        TypePrint(line);
    }

    file.close();
}
