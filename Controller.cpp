#include "Controller.h"
#include "BattleSystem.h"
#include <iostream>
#include <conio.h>
#include <ctime>

Controller::Controller(Player& player, Boss& boss, Map& map)
    : player(player), boss(boss), map(map) {
}

void Controller::startGame() 
{
    srand(static_cast<unsigned>(time(0)));
    std::cout << "주인공의 이름을 입력하세요: ";
    std::getline(std::cin, player.name); //플레이어 이름 설정

    map.initialize();
    char input;
    bool running = true;

    while (running) 
    {
        map.print(player, playerX, playerY);
        input = _getch();

        if (input == 'q' || input == 'Q') //q 입력시 종료
        {
            running = false;
        }
        else if (movePlayer(input)) 
        {
            if (map.getTile(playerX, playerY) == 'P') 
            {
                BattleSystem bs;
                bs.fight(player, boss);
                running = false;
            }
        }
    }

    std::cout << "게임 종료!" << std::endl;
}

bool Controller::movePlayer(char input) 
{
    int newX = playerX, newY = playerY;
    switch (input) {
    case 'w': case 'W': newY--; break; //w,W 입력시 Y-1 (위로)
    case 's': case 'S': newY++; break; //s,S 입력시 Y+1 (밑으로)
    case 'a': case 'A': newX--; break; //a,A 입력시 X-1 (왼쪽으로)
    case 'd': case 'D': newX++; break; //d,D 입력시 X+1 (오른쪽으로)
    default: return false;
    }

    if (map.getTile(newX, newY) != '|' && map.getTile(newX, newY) != '-') 
    {
        playerX = newX;
        playerY = newY;
        return true;
    }
    return false;
}
