#include <iostream>
#include "LevelUp.h"
#include "Player.h"

using namespace std;

int main()
{
    Player player("테스트", "전사");
    LevelUp level;

    level.AddExp(&player, 50);
    level.PrintLevelInfo(&player);

    cout << endl;

    level.AddExp(&player, 60);
    level.PrintLevelInfo(&player);
}
