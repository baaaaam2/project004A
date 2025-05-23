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
    cout << "주인공의 이름을 입력하세요: ";
    getline(cin, player.name); //플레이어 이름 설정
    system("cls");
    printStartStory(player); // StorySystem.h에서 호출

    map.initialize();
    char input;
    bool running = true;
    char grade = 'F'; // 초기 학점

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
            if (map.getTile(playerX, playerY) == 'B') 
            {
                printBossEncounterStory(player);
                BattleSystem bs;
                bs.fight(player, bosses[0], grade);
                // 전투 결과에 따라 스토리 출력
                if (bosses[0].isDead())
                {
                    showEnding(player, grade); //엔딩 출력
                    printWinStory(player);
                }
                else if (player.isDead()) 
                {
                    showEnding(player, grade); //엔딩 출력
                    printLoseStory(player);
                }
                running = false;
            }
        }
    }
    cout << "\n게임 종료!" << endl;
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

    if (map.getTile(newX, newY) != '|' && map.getTile(newX, newY) != '-' && map.getTile(newX, newY) != '+')
    {
        playerX = newX;
        playerY = newY;

        int chance = rand() % 100; // 랜덤 확률 생성
        if (chance < 0) { //확률 바꾸기
            int friendindex = 3 + rand() % 3; // 친구 보스 중 하나 선택
            std::cout << bosses[friendindex].name << "와(과) 조우했습니다!\n";
            BattleSystem bs;
            bs.fightfriend(player, bosses[friendindex]);
            // 플레이어가 죽었으면 이동 실패 처리
            if (player.isDead()) {
                std::cout << "플레이어가 사망했습니다.\n";
                return false;
            }
        }
        return true;
    }
    return false;
}
