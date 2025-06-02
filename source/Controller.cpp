�?#include "Controller.h"
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

    // 교수?�� 보스 3명의 고정 좌표 �??��
    bossMap[{21, 2}] = 0;  // �?코딩 교수?��
    bossMap[{6, 14}] = 1;  // 조객�? 교수?��
    bossMap[{24, 18}] = 2; // 박게?�� 교수?��
}

int Controller::getRemainingBossCount() const
{
    int count = 0;
    for (size_t i = 0; i < bosses.size(); ++i) {
        if (!defeatedBosses[i] && bosses[i].name.find("교수?��") != string::npos) { // 교수?�� ?��름이 ?��?��?�� 보스�? 카운?��
            count++;
        }
    }
    return count;
}

void Controller::startGame()
{
    srand(static_cast<unsigned>(time(0)));
    cout << "주인공의 ?��름을 ?��?��?��?��?�� : ";
    getline(cin, player.name); //?��?��?��?�� ?���? ?��?��
    system("cls");
    printStartStory(player); // StorySystem.h?��?�� ?���?

    map.initialize();
    for (const auto& entry : bossMap) { // 보스 ?���? ?��?��
        map.setTile(entry.first.first, entry.first.second, 'B');
    }
    char input;
    bool running = true;

    while (running)
    {
        map.print(player, playerX, playerY, getRemainingBossCount());
        input = _getch();

        if (input == 'q' || input == 'Q') //q ?��?��?�� 종료
        {
            running = false;
        }
        else if (movePlayer(input))
        {
            pair<int, int> currentPos = { playerX, playerY };
            if (map.getTile(playerX, playerY) == 'S') //?��?�� ?��?��
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
						cout << bosses[bossIndex].getName() << " ?��(�?) 처치?��?��?��?��!\n" << endl;
						printWinStory(player);
                    }
                    else {
						cout << "\n";
                        cout << bosses[bossIndex].getName() << " 과의 ?��?��?��?�� ?��배했?��?��?��...\n" << endl;
                        printLoseStory(player);
                    }
					// 보스 ?��?�� ?�� ?��?��?��?���? 죽�?? 경우
                    if (getRemainingBossCount() != 0 && player.isDead()) {
						system("cls");
                        printLine("?��?��?��?���? 기절?��?���? 기숙?��?��?�� 깨어?��?��?��?��..\n");
                        cout << "(계속?��?���? ?���? ?��?�� ?��르세?��...)\n";
                        _getch(); // ?�� ?��?�� ???�?
						player.hp = player.maxHP; // ?��?��?��?�� 체력 ?���?
						playerX = 1; // ?��?��?��?�� ?���? 초기?��
						playerY = 1; // ?��?��?��?�� ?���? 초기?��
                        continue;
                    }
                }
            }

            if (getRemainingBossCount() <= 0) // 모든 교수?��?�� 처치?�� 경우(?��?��?�� 모두 ?�� 경우)
            {
                showEnding(player);
                running = false;
            }
        }
    }
    
    cout << "\n게임 종료!" << endl;
	cout << "?��?��치느?�� 고생?��?��?��?��?��!\n";
}

bool Controller::movePlayer(char input) 
{
    int newX = playerX, newY = playerY;
    switch (input) {
    case 'w': case 'W': newY--; break; //w,W ?��?��?�� Y-1 (?���?)
    case 's': case 'S': newY++; break; //s,S ?��?��?�� Y+1 (밑으�?)
    case 'a': case 'A': newX--; break; //a,A ?��?��?�� X-1 (?��쪽으�?)
    case 'd': case 'D': newX++; break; //d,D ?��?��?�� X+1 (?��른쪽?���?)
    default: return false;
    }

    char tile = map.getTile(newX, newY);
    // ?��?�� �??��?�� ????���? ?��?�� (공백 ?��?�� 'S' ?���? ?��)
    if (tile == ' ' || tile == 'S' || tile =='B') {
        playerX = newX;
        playerY = newY;

        int chance = rand() % 100;
        if (chance < 0) { // ?��?��?�� ?��?�� ?��?�� ?�� ?�� (?���? 조건 ?��?�� ?��?��)
            int friendindex = 3 + rand() % 3;
            std::cout << bosses[friendindex].name << "???(�?) 조우?��?��?��?��!\n";
            BattleSystem bs;
            bs.fightfriend(player, bosses[friendindex]);
            bosses[friendindex].hp = bosses[friendindex].maxHP;
            Sleep(1500);
            if (getRemainingBossCount() != 0 && player.isDead()) 
            {
                system("cls");
                printLine("�÷��̾ �����ߴٰ� ����翡�� ������ϴ�..\n");
                cout << "(����Ϸ��� �ƹ� Ű�� ��������...)\n";
                _getch(); // Ű �Է� ���
                player.hp = player.maxHP; // �÷��̾� ü�� ȸ��
                playerX = 1; // �÷��̾� ��ġ �ʱ�ȭ
                playerY = 1; // �÷��̾� ��ġ �ʱ�ȭ
            }
        }

        return true;
    }

    return false;
}
