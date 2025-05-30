#include "Controller.h"
#include "Player.h"
#include "BattleSystem.h"
#include "StorySystem.h"
#include "Shop.h"
#include <iostream>
#include <conio.h>
#include <ctime>
#include <windows.h>

using namespace std;

Controller::Controller(Player& player, vector<Boss> bosses, Map& map)
    : player(player), bosses(move(bosses)), map(map), defeatedBosses(this->bosses.size(), false) {

    // 교수님 보스 3명의 고정 좌표 지정
    bossMap[{21, 2}] = 0;  // 김코딩 교수님
    bossMap[{6, 14}] = 1;  // 조객체 교수님
    bossMap[{24, 18}] = 2; // 박게임 교수님
}

int Controller::getRemainingBossCount() const
{
    int count = 0;
    for (size_t i = 0; i < bosses.size(); ++i) {
        if (!defeatedBosses[i] && bosses[i].name.find("교수님") != string::npos) { // 교수님 이름이 포함된 보스만 카운트
            count++;
        }
    }
    return count;
}

void Controller::startGame()
{
    srand(static_cast<unsigned>(time(0)));
    cout << "주인공의 이름을 입력하세요: ";
    getline(cin, player.name); //플레이어 이름 설정
    system("cls");
    printStartStory(player); // StorySystem.h에서 호출

    map.initialize();
    for (const auto& entry : bossMap) { // 보스 위치 설정
        map.setTile(entry.first.first, entry.first.second, 'B');
    }
    char input;
    bool running = true;
    double gpa = 0.0;

    while (running)
    {
        map.print(player, playerX, playerY, getRemainingBossCount());
        input = _getch();

        if (input == 'q' || input == 'Q') //q 입력시 종료
        {
            running = false;
        }
        else if (movePlayer(input))
        {
            pair<int, int> currentPos = { playerX, playerY };
            if (map.getTile(playerX, playerY) == 'S') //상점 입장
            {
                Shop shop;
                shop.enterShop(player);
            }
            if (bossMap.count(currentPos)) {
                int bossIndex = bossMap[currentPos];

                if (!defeatedBosses[bossIndex]) {
                    printBossEncounterStory(player);
                    BattleSystem bs;
                    bs.fight(player, bosses[bossIndex], gpa);

                    defeatedBosses[bossIndex] = true;
                    map.setTile(playerX, playerY, '.');

                    if (bosses[bossIndex].isDead()) {
                        cout << bosses[bossIndex].getName() << " 을(를) 처치했습니다!\n";
                    }
                    else {
                        cout << bosses[bossIndex].getName() << " 과의 전투에서 패배했습니다...\n";
                    }
                    Sleep(1500);

                    if (player.isDead()) {
                        //printLoseStory(player);
                        // 플레이어가 죽었을 때 부활 처리
                        continue;
                    }
                }
            }

            if (getRemainingBossCount() <= 0) // 모든 교수님을 처치한 경우(시험을 모두 푼 경우)
            {
                cout << "\n시험이 끝났습니다!";
                showEnding(player, gpa);
                running = false;
            }
        }
    }
    cout << "게임 종료!" << endl;
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
            /*if (player.isDead()) {
                std::cout << "플레이어가 사망했습니다.\n";
                return false;
            }*/
        }
        return true;
    }
    return false;
}
