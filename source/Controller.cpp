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

    // ������ ���� 3���� ���� ��ǥ ����
    bossMap[{21, 2}] = 0;  // ���ڵ� ������
    bossMap[{6, 14}] = 1;  // ����ü ������
    bossMap[{24, 18}] = 2; // �ڰ��� ������
}

int Controller::getRemainingBossCount() const
{
    int count = 0;
    for (size_t i = 0; i < bosses.size(); ++i) {
        if (!defeatedBosses[i] && bosses[i].name.find("������") != string::npos) { // ������ �̸��� ���Ե� ������ ī��Ʈ
            count++;
        }
    }
    return count;
}

void Controller::startGame()
{
    srand(static_cast<unsigned>(time(0)));
    cout << "���ΰ��� �̸��� �Է��ϼ��� : ";
    getline(cin, player.name); //�÷��̾� �̸� ����
    system("cls");
    printStartStory(player); // StorySystem.h���� ȣ��

    map.initialize();
    for (const auto& entry : bossMap) { // ���� ��ġ ����
        map.setTile(entry.first.first, entry.first.second, 'B');
    }
    char input;
    bool running = true;

    while (running)
    {
        map.print(player, playerX, playerY, getRemainingBossCount());
        input = _getch();

        if (input == 'q' || input == 'Q') //q �Է½� ����
        {
            running = false;
        }
        else if (movePlayer(input))
        {
            pair<int, int> currentPos = { playerX, playerY };
            if (map.getTile(playerX, playerY) == 'S') //���� ����
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
						cout << bosses[bossIndex].getName() << " ��(��) óġ�߽��ϴ�!\n" << endl;
						printWinStory(player);
                    }
                    else {
						cout << "\n";
                        cout << bosses[bossIndex].getName() << " ���� �������� �й��߽��ϴ�...\n" << endl;
                        printLoseStory(player);
                    }
					// ���� ���� �� �÷��̾ ���� ���
                    if (getRemainingBossCount() != 0 && player.isDead()) {
						system("cls");
                        printLine("�÷��̾ �����ߴٰ� ����翡�� ������ϴ�..\n");
                        cout << "(����Ϸ��� �ƹ� Ű�� ��������...)\n";
                        _getch(); // Ű �Է� ���
						player.hp = player.maxHP; // �÷��̾� ü�� ȸ��
						playerX = 1; // �÷��̾� ��ġ �ʱ�ȭ
						playerY = 1; // �÷��̾� ��ġ �ʱ�ȭ
                        continue;
                    }
                }
            }

            if (getRemainingBossCount() <= 0) // ��� �������� óġ�� ���(������ ��� Ǭ ���)
            {
                showEnding(player);
                running = false;
            }
        }
    }
    
    cout << "\n���� ����!" << endl;
	cout << "����ġ���� ����ϼ̽��ϴ�!\n";
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

    char tile = map.getTile(newX, newY);
    // �̵� ������ Ÿ�ϸ� ��� (���� �Ǵ� 'S' ��ġ ��)
    if (tile == ' ' || tile == 'S' || tile =='B') {
        playerX = newX;
        playerY = newY;

        int chance = rand() % 100;
        if (chance < 8) { // ����� �׻� ���� �� �� (Ȯ�� ���� ���� �ʿ�)
            int friendindex = 3 + rand() % 3;
            std::cout << bosses[friendindex].name << "��(��) �����߽��ϴ�!\n";
            BattleSystem bs;
            bs.fightfriend(player, bosses[friendindex]);
            bosses[friendindex].hp = bosses[friendindex].maxHP;
            Sleep(1500);
            if(getRemainingBossCount() != 0 && player.isDead())
            {
                system("cls");
                printLine("�÷��̾ �����ߴٰ� ����翡�� ������ϴ�..\n");
                player.hp = player.maxHP; // HP�� �ִ�ġ�� �ʱ�ȭ
                playerX = 1;
                playerY = 1;
                Sleep(2000);
            }
        }

        return true;
    }

    return false;
}
