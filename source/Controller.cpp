#include "Controller.h"
#include "Player.h"
#include "BattleSystem.h"
#include "StorySystem.h"
#include <iostream>
#include <conio.h>
#include <ctime>

using namespace std;

Controller::Controller(Player& player, vector<Boss> bosses, Map& map)
    : player(player), bosses(move(bosses)), map(map) {
}

void Controller::startGame()
{
    srand(static_cast<unsigned>(time(0)));
    cout << "���ΰ��� �̸��� �Է��ϼ���: ";
    getline(cin, player.name); //�÷��̾� �̸� ����
    system("cls");
    printStartStory(player); // StorySystem.h���� ȣ��

    map.initialize();
    char input;
    bool running = true;
    char grade = 'F'; // �ʱ� ����

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
            if (map.getTile(playerX, playerY) == 'B') 
            {
                printBossEncounterStory(player);
                BattleSystem bs;
                bs.fight(player, bosses[0], grade);
                // ���� ����� ���� ���丮 ���
                if (bosses[0].isDead())
                {
                    showEnding(player, grade); //���� ���
                    printWinStory(player);
                }
                else if (player.isDead()) 
                {
                    showEnding(player, grade); //���� ���
                    printLoseStory(player);
                }
                running = false;
            }
        }
    }
    cout << "\n���� ����!" << endl;
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

    if (map.getTile(newX, newY) != '|' && map.getTile(newX, newY) != '-' && map.getTile(newX, newY) != '+')
    {
        playerX = newX;
        playerY = newY;

        int chance = rand() % 100; // ���� Ȯ�� ����
        if (chance < 0) { //Ȯ�� �ٲٱ�
            int friendindex = 3 + rand() % 3; // ģ�� ���� �� �ϳ� ����
            std::cout << bosses[friendindex].name << "��(��) �����߽��ϴ�!\n";
            BattleSystem bs;
            bs.fightfriend(player, bosses[friendindex]);
            // �÷��̾ �׾����� �̵� ���� ó��
            if (player.isDead()) {
                std::cout << "�÷��̾ ����߽��ϴ�.\n";
                return false;
            }
        }
        return true;
    }
    return false;
}
