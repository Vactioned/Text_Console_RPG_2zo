#include "LogManager.h"
#include "BattleSystem.h"

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
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
    }

    cout << "\n[ 엔터(Enter)를 누르면 계속합니다... ]";

    cin.ignore(cin.rdbuf()->in_avail(), '\n');

    cin.get(); // 사용자가 엔터를 누를 때까지 대기
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

void LogManager::MainMenu(Player& player, Inventory<Item>& inventory)
{
    static BattleSystem bs;

    int select;
    bool isGameStart = true;    // 현재 게임이 진행 중인지 판단

    while (isGameStart)
    {
        LogManager::Clear();

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
            bs.EnterMissionMenu(player, inventory);
            LogManager::PressEnter();
            break;
        case 2:
            player.PrintPlayerStatus();
            PressEnter();
            break;
        case 3:
            InventoryUI inventoryUI;
            inventoryUI.Open(inventory, &player, false);
            PressEnter();
            break;
        case 4:
            isGameStart = false;
            cout << "게임을 종료합니다." << endl;
            break;
        default:
            cout << "   잘못된 선택입니다. 다시 선택해주세요." << endl;
            break;
        }
    }
}

void LogManager::CH1()      // 1막 메인 스토리
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

void LogManager::CH1_Boss()     // 1막 보스전
{
    ifstream file("CH1_Boss.txt");

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

string LogManager::InputPlayerName()        // 이름 입력 함수
{
    string name;
    cout << "================================================================" << endl;
    cout << "                       나의 이름은 무엇인가                        " << endl;
    cout << "================================================================" << endl;
    cout << "입력 : ";
    cin >> name;

    return name;
}

string LogManager::SelectJob()              // 직업 입력 함수
{
    int choice;
    string job = "";

    while (true)
    {
        cout << "================================================================" << endl;
        cout << "                      나의 직업은 무엇인가                         " << endl;
        cout << "================================================================" << endl;
        cout << " [선택 1] : 버서커" << endl;
        cout << " [선택 2] : 흑마법사" << endl;
        cout << " [선택 3] : 도적" << endl;
        cout << " [선택 4] : 수도승" << endl;
        cout << " [선택 5] : 도파민 상자 (당신의 운을 시험하세요)" << endl;
        cout << "입력 : ";
        cin >> choice;

        switch (choice)
        {
        case 1: job = "Berserker"; break;
        case 2: job = "Warlock"; break;
        case 3: job = "Thief"; break;
        case 4: job = "Monk"; break;
        case 5:
        {
            srand(static_cast<unsigned int>(time(NULL)));

            // 1~100 사이의 난수를 발생
            int chance = (rand() % 100) + 1;
            job = (chance <= 80) ? "Poor" : "Gambler";
            break;
        }
        default:
            cout << "\n [오류] 잘못된 선택입니다. 다시 입력해주세요." << endl;
            continue;
        }
        if (job != "") break;
    }
    return job;
}
