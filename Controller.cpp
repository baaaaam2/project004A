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
    std::cout << "���ΰ��� �̸��� �Է��ϼ���: ";
    std::getline(std::cin, player.name); //�÷��̾� �̸� ����

    map.initialize();
    char input;
    bool running = true;

    while (running) 
    {
        map.print(player, playerX, playerY);
        input = _getch();

        if (input == 'q' || input == 'Q') //q �Է½� ����
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

    std::cout << "���� ����!" << std::endl;
}

bool Controller::movePlayer(char input) 
{
    int newX = playerX, newY = playerY;
    switch (input) {
    case 'w': case 'W': newY--; break; //w,W �Է½� Y-1 (����)
    case 's': case 'S': newY++; break; //s,S �Է½� Y+1 (������)
    case 'a': case 'A': newX--; break; //a,A �Է½� X-1 (��������)
    case 'd': case 'D': newX++; break; //d,D �Է½� X+1 (����������)
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
