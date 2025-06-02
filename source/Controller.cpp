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
    cout << "주인공의 이름을 입력하세요 : ";
    getline(cin, player.name); //플레이어 이름 설정
    system("cls");
    printStartStory(player); // StorySystem.h에서 호출

    map.initialize();
    for (const auto& entry : bossMap) { // 보스 위치 설정
        map.setTile(entry.first.first, entry.first.second, 'B');
    }
    char input;
    bool running = true;

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
                    bs.fight(player, bosses[bossIndex]);

                    defeatedBosses[bossIndex] = true;
                    map.setTile(playerX, playerY, ' ');
                    if (bosses[bossIndex].isDead()) {
                        cout << "\n";
						cout << bosses[bossIndex].getName() << " 을(를) 처치했습니다!\n" << endl;
						printWinStory(player);
                    }
                    else {
						cout << "\n";
                        cout << bosses[bossIndex].getName() << " 과의 전투에서 패배했습니다...\n" << endl;
                        printLoseStory(player);
                    }
					// 보스 전투 후 플레이어가 죽은 경우
                    if (getRemainingBossCount() != 0 && player.isDead()) {
						system("cls");
                        printLine("플레이어가 기절했다가 기숙사에서 깨어났습니다..\n");
                        cout << "(계속하려면 아무 키나 누르세요...)\n";
                        _getch(); // 키 입력 대기
						player.hp = player.maxHP; // 플레이어 체력 회복
						playerX = 1; // 플레이어 위치 초기화
						playerY = 1; // 플레이어 위치 초기화
                        continue;
                    }
                }
            }

            if (getRemainingBossCount() <= 0) // 모든 교수님을 처치한 경우(시험을 모두 푼 경우)
            {
                showEnding(player);
                running = false;
            }
        }
    }
    
    cout << "\n게임 종료!" << endl;
	cout << "시험치느라 고생하셨습니다!\n";
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

    char tile = map.getTile(newX, newY);
    // 이동 가능한 타일만 허용 (공백 또는 'S' 위치 등)
    if (tile == ' ' || tile == 'S' || tile =='B') {
        playerX = newX;
        playerY = newY;

        int chance = rand() % 100;
        if (chance < 8) { // 현재는 항상 실행 안 됨 (확률 조건 수정 필요)
            int friendindex = 3 + rand() % 3;
            std::cout << bosses[friendindex].name << "와(과) 조우했습니다!\n";
            BattleSystem bs;
            bs.fightfriend(player, bosses[friendindex]);
            bosses[friendindex].hp = bosses[friendindex].maxHP;
            Sleep(1500);
            if(getRemainingBossCount() != 0 && player.isDead())
            {
                system("cls");
                printLine("플레이어가 기절했다가 기숙사에서 깨어났습니다..\n");
                player.hp = player.maxHP; // HP를 최대치로 초기화
                playerX = 1;
                playerY = 1;
                Sleep(2000);
            }
        }

        return true;
    }

    return false;
}
