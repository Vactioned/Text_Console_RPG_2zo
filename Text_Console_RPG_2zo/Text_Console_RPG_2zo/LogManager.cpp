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

int GetSafeInput()
{
    int input;

    while (true)
    {
        if (cin >> input)
        {
            cin.ignore(10000, '\n');
            return input;
        }
        else
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "================================================================" << endl;
            cout << " [오류] 숫자로만 입력해주세요 : ";
        }
    }
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
    cout << "\n[ 엔터(Enter)를 누르면 계속합니다... ]" << flush;

    cin.clear();
    cin.sync();  // 이전 cin >> 으로 남은 버퍼 비우기 (Windows MSVC 안정)
    cin.get();   // 실제 엔터 대기

    cout << "\r" << string(80, ' ') << "\r" << flush;
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

        // UTF-8 한글 처리 (3바이트 패턴 확인: 1110xxxx)
        if ((unsigned char)message[i] >= 0xE0 && i + 2 < message.length())
        {
            cout << message[i] << message[i + 1] << message[i + 2] << flush;
            i += 2;
        }
        else
        {
            cout << message[i] << flush;
        }

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
        cout << "입력 : ";
        select = GetSafeInput();

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
            cout << "================================================================" << endl;
            cout << "게임을 종료합니다." << endl;
            break;
        default:          
            cout << "   잘못된 선택입니다. 다시 선택해주세요." << endl;
            PressEnter();
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
        return;
    }

    cout << "\n";
    string line;
    bool isAsciiMode = false;
    while (getline(file, line))
    {
        if (line.find("@@@") != string::npos)
        {
            isAsciiMode = !isAsciiMode;
            continue;
        }

        if (isAsciiMode) cout << line << endl;
        else            TypePrint(line);
    }

    cout << "\n";
    file.close();
}

void LogManager::CH1_Boss()     // 1막 보스전
{
    ifstream file("CH1_Boss.txt");

    if (!file.is_open())
    {
        cout << "파일을 열 수 없습니다.\n";
        return;
    }

    cout << "\n";
    string line;
    bool isAsciiMode = false;
    while (getline(file, line))
    {
        if (line.find("@@@") != string::npos)
        {
            isAsciiMode = !isAsciiMode;
            continue;
        }

        if (isAsciiMode) cout << line << endl;
        else            TypePrint(line);
    }

    cout << "\n";
    file.close();
}

void LogManager::CH2()     // 2막 메인 스토리
{
    ifstream file("CH2.txt");

    if (!file.is_open())
    {
        cout << "파일을 열 수 없습니다.\n";
        return;
    }

    cout << "\n";
    string line;
    bool isAsciiMode = false;
    while (getline(file, line))
    {
        if (line.find("@@@") != string::npos)
        {
            isAsciiMode = !isAsciiMode;
            continue;
        }

        if (isAsciiMode) cout << line << endl;
        else            TypePrint(line);
    }

    cout << "\n";
    file.close();
}

void LogManager::CH2_Boss()     // 2막 보스전
{
    ifstream file("CH2_Boss.txt");

    if (!file.is_open())
    {
        cout << "파일을 열 수 없습니다.\n";
        return;
    }

    cout << "\n";
    string line;
    bool isAsciiMode = false;
    while (getline(file, line))
    {
        if (line.find("@@@") != string::npos)
        {
            isAsciiMode = !isAsciiMode;
            continue;
        }

        if (isAsciiMode) cout << line << endl;
        else            TypePrint(line);
    }

    cout << "\n";
    file.close();
}
void LogManager::CH3()     // 3막 메인 스토리
{
    ifstream file("CH3.txt");

    if (!file.is_open())
    {
        cout << "파일을 열 수 없습니다.\n";
        return;
    }

    cout << "\n";
    string line;
    bool isAsciiMode = false;
    while (getline(file, line))
    {
        if (line.find("@@@") != string::npos)
        {
            isAsciiMode = !isAsciiMode;
            continue;
        }

        if (isAsciiMode) cout << line << endl;
        else            TypePrint(line);
    }

    cout << "\n";
    file.close();
}
void LogManager::CH3_Boss()     // 3막 보스전
{
    ifstream file("CH3_Boss.txt");

    if (!file.is_open())
    {
        cout << "파일을 열 수 없습니다.\n";
        return;
    }

    cout << "\n";
    string line;
    bool isAsciiMode = false;
    while (getline(file, line))
    {
        if (line.find("@@@") != string::npos)
        {
            isAsciiMode = !isAsciiMode;
            continue;
        }

        if (isAsciiMode) cout << line << endl;
        else            TypePrint(line);
    }

    cout << "\n";
    file.close();
}
void LogManager::CH4()     // 4막 메인 스토리
{
    ifstream file("CH4.txt");

    if (!file.is_open())
    {
        cout << "파일을 열 수 없습니다.\n";
        return;
    }

    cout << "\n";
    string line;
    bool isAsciiMode = false;
    while (getline(file, line))
    {
        if (line.find("@@@") != string::npos)
        {
            isAsciiMode = !isAsciiMode;
            continue;
        }

        if (isAsciiMode) cout << line << endl;
        else            TypePrint(line);
    }

    cout << "\n";
    file.close();
}
void LogManager::CH4_Boss()     // 4막 보스전
{
    ifstream file("CH4_Boss.txt");

    if (!file.is_open())
    {
        cout << "파일을 열 수 없습니다.\n";
        return;
    }

    cout << "\n";
    string line;
    bool isAsciiMode = false;
    while (getline(file, line))
    {
        if (line.find("@@@") != string::npos)
        {
            isAsciiMode = !isAsciiMode;
            continue;
        }

        if (isAsciiMode) cout << line << endl;
        else            TypePrint(line);
    }

    cout << "\n";
    file.close();
}
void LogManager::CH5()     // 5막 메인 스토리
{
    ifstream file("CH5.txt");

    if (!file.is_open())
    {
        cout << "파일을 열 수 없습니다.\n";
        return;
    }

    cout << "\n";
    string line;
    bool isAsciiMode = false;
    while (getline(file, line))
    {
        if (line.find("@@@") != string::npos)
        {
            isAsciiMode = !isAsciiMode;
            continue;
        }

        if (isAsciiMode) cout << line << endl;
        else            TypePrint(line);
    }

    cout << "\n";
    file.close();
}
void LogManager::CH5_Choice()     // 5막 엔딩 분기점
{
    ifstream file("CH5_Choice.txt");

    if (!file.is_open())
    {
        cout << "파일을 열 수 없습니다.\n";
        return;
    }

    cout << "\n";
    string line;
    bool isAsciiMode = false;
    while (getline(file, line))
    {
        if (line.find("@@@") != string::npos)
        {
            isAsciiMode = !isAsciiMode;
            continue;
        }

        if (isAsciiMode) cout << line << endl;
        else            TypePrint(line);
    }

    cout << "\n";
    file.close();
}

void LogManager::Final_Boss_1()
{
    ifstream file("Final_Boss_1.txt");

    if (!file.is_open())
    {
        cout << "파일을 열 수 없습니다.\n";
        return;
    }

    cout << "\n";
    string line;
    bool isAsciiMode = false;
    while (getline(file, line))
    {
        if (line.find("@@@") != string::npos)
        {
            isAsciiMode = !isAsciiMode;
            continue;
        }

        if (isAsciiMode) cout << line << endl;
        else            TypePrint(line);
    }

    cout << "\n";
    file.close();
}

void LogManager::Final_Boss_2()
{
    ifstream file("Final_Boss_2.txt");

    if (!file.is_open())
    {
        cout << "파일을 열 수 없습니다.\n";
        return;
    }

    cout << "\n";
    string line;
    bool isAsciiMode = false;
    while (getline(file, line))
    {
        if (line.find("@@@") != string::npos)
        {
            isAsciiMode = !isAsciiMode;
            continue;
        }

        if (isAsciiMode) cout << line << endl;
        else            TypePrint(line);
    }

    cout << "\n";
    file.close();
}

void LogManager::HAPPY_END()     // 해피 엔딩?
{
    ifstream file("HAPPY_END.txt");

    if (!file.is_open())
    {
        cout << "파일을 열 수 없습니다.\n";
        return;
    }

    cout << "\n";
    string line;
    bool isAsciiMode = false;
    while (getline(file, line))
    {
        if (line.find("@@@") != string::npos)
        {
            isAsciiMode = !isAsciiMode;
            continue;
        }

        if (isAsciiMode) cout << line << endl;
        else            TypePrint(line);
    }

    cout << "\n";
    file.close();
}

void LogManager::BAD_END()     // 배드 엔딩
{
    ifstream file("BAD_END.txt");

    if (!file.is_open())
    {
        cout << "파일을 열 수 없습니다.\n";
        return;
    }

    cout << "\n";
    string line;
    bool isAsciiMode = false;
    while (getline(file, line))
    {
        if (line.find("@@@") != string::npos)
        {
            isAsciiMode = !isAsciiMode;
            continue;
        }

        if (isAsciiMode) cout << line << endl;
        else            TypePrint(line);
    }

    cout << "\n";
    file.close();
}

void LogManager::PrintAsciiFile(const string& filename)
{
    ifstream file(filename);
    if (!file.is_open()) return;
    string line;
    while (getline(file, line))
        cout << line << "\n";
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
        cout << " [선택 4] : 파계승" << endl;
        cout << " [선택 5] : 도파민 상자 (당신의 운을 시험하세요)" << endl;
        cout << "================================================================" << endl;
        cout << "입력 : ";
        choice = GetSafeInput();
        cout << endl;

        switch (choice)
        {
        case 1: job = "Berserker";
            cout << "================================================================" << endl;
            cout << "<버서커>" << endl;
            cout << "\"닥치고 피나 쏟아내라. 이 미친 갈증을 채우려면 멀었어.\"" << endl;
            cout << "자신의 살점이 떨어져 나가는 고통마저 살육의 희열로 바꾸는 광전사" << endl;
            cout << "================================================================" << endl;
            break;
        case 2: job = "Warlock";
            cout << "================================================================" << endl;
            cout << "<흑마법사>" << endl;
            cout << "\"세상이 금기라고 부르는 것들? 나한테는 다 힘일 뿐이야.\"" << endl;
            cout << "금단의 지식을 탐한 대가로 강력한 파괴의 권능을 얻은 자" << endl;
            cout << "================================================================" << endl;
            break;
        case 3: job = "Thief";
            cout << "================================================================" << endl;
            cout << "<도적>" << endl;
            cout << "\"영웅 놀이는 딴 데 가서 해. 난 내 몫 챙겨서 살 궁리나 할 테니까.\"" << endl;
            cout << "혼란을 틈타 오직 자신만의 생존과 이득을 취하는 무법자" << endl;
            cout << "================================================================" << endl;
            break;
        case 4: job = "Monk";
            cout << "================================================================" << endl;
            cout << "<파계승>" << endl;
            cout << "\"계율이 밥 먹여 줍니까? 살길은 내가 알아서 만듭니다.\"" << endl;
            cout << "종교의 규율을 깨부수고 독자적인 정신의 경지에 이른 자" << endl;
            cout << "================================================================" << endl;
            break;
        case 5:
        {
            srand(static_cast<unsigned int>(time(NULL)));

            // 1~6 사이의 난수를 발생 (총 6개의 모든 직업)
            int randomRoll = (rand() % 6) + 1;

            cout << "\n[도파민 상자 개방!] 주사위가 굴러갑니다... 결과는?! \n" << endl;

            switch (randomRoll)
            {
            case 1: job = "Berserker";
                cout << "================================================================" << endl;
                cout << "<버서커>" << endl;
                cout << "\"닥치고 피나 쏟아내라. 이 미친 갈증을 채우려면 멀었어.\"" << endl;
                cout << "자신의 살점이 떨어져 나가는 고통마저 살육의 희열로 바꾸는 광전사" << endl;
                cout << "================================================================" << endl;
                break;
            case 2: job = "Warlock";
                cout << "================================================================" << endl;
                cout << "<흑마법사>" << endl;
                cout << "\"세상이 금기라고 부르는 것들? 나한테는 다 힘일 뿐이야.\"" << endl;
                cout << "금단의 지식을 탐한 대가로 강력한 파괴의 권능을 얻은 자" << endl;
                cout << "================================================================" << endl;
                break;
            case 3: job = "Thief";
                cout << "================================================================" << endl;
                cout << "<도적>" << endl;
                cout << "\"영웅 놀이는 딴 데 가서 해. 난 내 몫 챙겨서 살 궁리나 할 테니까.\"" << endl;
                cout << "혼란을 틈타 오직 자신만의 생존과 이득을 취하는 무법자" << endl;
                cout << "================================================================" << endl;
                break;
            case 4: job = "Monk";
                cout << "================================================================" << endl;
                cout << "<파계승>" << endl;
                cout << "\"계율이 밥 먹여 줍니까? 살길은 내가 알아서 만듭니다.\"" << endl;
                cout << "종교의 규율을 깨부수고 독자적인 정신의 경지에 이른 자" << endl;
                cout << "================================================================" << endl;
                break;
            case 5:
                job = "Poor";
                cout << "================================================================" << endl;
                cout << "<부랑자>" << endl;
                cout << "\"배가 너무 고파요... 먹을 것 좀 나눠주십쇼...\"" << endl;
                cout << "인생의 바닥에서 하루하루 간신히 살아가는 비참한 부랑자" << endl;
                cout << "================================================================" << endl;
                break;
            case 6:
                job = "Gambler";
                cout << "================================================================" << endl;
                cout << "<도박꾼>" << endl;
                cout << "\"너 그거 중독이야!\"" << endl;
                cout << "확률의 신을 믿으며 모든 것을 판돈으로 거는 위험한 도박꾼" << endl;
                cout << "================================================================" << endl;
                break;
            }
            break;
        }
        default:
            cout << "\n [오류] 잘못된 선택입니다. 다시 입력해주세요." << endl;
            continue;
        }
        if (job != "")
        {
            if      (job == "Berserker") PrintAsciiFile("Berserker.txt");
            else if (job == "Warlock")   PrintAsciiFile("Warlok.txt");
            else if (job == "Thief")     PrintAsciiFile("Thief.txt");
            else if (job == "Monk")      PrintAsciiFile("Monk.txt");
            else if (job == "Poor")      PrintAsciiFile("Poor.txt");
            else if (job == "Gambler")   PrintAsciiFile("Gambler.txt");
            break;
        }
    }
    return job;
}
