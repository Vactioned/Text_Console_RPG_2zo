#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <iostream>
#include <string>

#include "LogManager.h"
#include "Player.h"
#include "Inventory.h"
#include "Classes.h"

using namespace std;



int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    cout << "================================================================" << endl;
    cout << "                       금단의 의식: 이형의 당도                    " << endl;
    cout << "================================================================" << endl;
    cout << " 인간이 느끼는 가장 강력하고 오래된 감정은 공포이다.    	            " << endl;
    cout << " 또한 인간이 느끼는 가장 강력하고 오래된 공포는, 미지에 대한 공포이다. " << endl;
    cout << "                                          - 러브크래프트 -		" << endl;
    cout << "================================================================" << endl;
    LogManager::PressEnter();

    LogManager::Clear();

    string playerName = LogManager::InputPlayerName();  // 이름 입력 함수

    LogManager::Clear();

    string jobName = LogManager::SelectJob();   // 직업 입력 함수

    Player* player = nullptr;

    if (jobName == "Berserker") player = new Berserker(playerName, "버서커");
    else if (jobName == "Warlock") player = new Warlock(playerName, "흑마법사");
    else if (jobName == "Thief")   player = new Thief(playerName, "도적");
    else if (jobName == "Monk")    player = new Monk(playerName, "파계승");
    else if (jobName == "Gambler") player = new Gambler(playerName, "도박꾼");
    else                           player = new Poor(playerName, "부랑자");

    LogManager::PressEnter();

    LogManager::Clear();
    cout << "================================================================" << endl;
    LogManager::TypePrint(" 세상은 생각보다 쉽게 무너진다.");
    LogManager::TypePrint(" 법과 질서가 아닌, 피와 광기에 의해서.");
    cout << endl;
    LogManager::TypePrint(" 한 광신도 집단이 저지른 짓은 단순한 학살이 아니었다.");
    LogManager::TypePrint(" 그들은 인간의 목숨을 화폐 삼아, 절대 열려서는 안 될 '차원의 문'을 열어젖혔다.");
    LogManager::TypePrint(" 그 균열을 타고 넘어온 기괴하고 거대한 존재들은 인간을 사냥감, 그 이하로 취급했다.");
    cout << endl;
    LogManager::TypePrint(" 그 여파는 최전방의 변방 마을부터 시작되었다.");
    LogManager::TypePrint(" 매일 밤 주민들이 사라졌다. 흔적도, 비명도 없이.");
    cout << endl;
    LogManager::TypePrint(" 교단도, 영주도 이 기괴한 실종 사건에서 고개를 돌렸을 때, 결국 움직이는 것은 용병들뿐이다.");
    LogManager::TypePrint(" 당신은 그저 짭짤한 보상과 소문의 진상을 쫓아 이 저주받은 땅에 도착했다.");
    LogManager::TypePrint(" 공기 중에 감도는 기분 나쁜 비린내.");
    LogManager::TypePrint(" 직감이 경고하고 있다. 이번 의뢰는 결코 만만치 않을 것이라고.");
    cout << "================================================================" << endl;
    LogManager::PressEnter();

    LogManager::Clear();

    Inventory<Item> inventory(10);

    LogManager::MainMenu(*player, inventory);

   

    delete player;

    return 0;
}
