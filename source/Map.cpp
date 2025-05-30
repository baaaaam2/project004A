#include "Map.h"
#include "Shop.h"
#include "Item.h"
#include "Player.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>

using namespace std;

//��
Map::Map() {
    initialize();
}
const char game_map[MAP_HEIGHT][MAP_WIDTH + 1] = {
    "+----------------------------+",  // 0
    "|     |        |  <�����>   |",  // 1 - ������ �� ���� ��
    "|     |        |             |",  // 2
    "|              +-----------  |",  // 3
    "|                            |",  // 4
    "|                            |",  // 5
    "|     +-----                 |",  // 6
    "|     | S              +-----|",  // 7
    "|     +-----           |     |",  // 8
    "|                      |     |",  // 9
    "|                      |     |",  // 10
    "|                            |",  // 11 - ���� �Ʒ� ���� ��
    "|----------                  |",  // 12
    "|  <�����>                  |",  // 13 - ������ �Ʒ� ���� ��
    "|                            |",  // 14
    "|----------                  |",  // 15
    "|                   +--------|",  // 16
    "|    ----+          |<�����>|",  // 17
    "|        |                   |",  // 18
    "+----------------------------+"   // 19
};


void Map::initialize()
{
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            tiles[y][x] = game_map[y][x];
        }
    }
}

void Map::print(const Player& player, int playerX, int playerY, int Bosses) {
    system("cls");
    //���ΰ� �̸�, �̵���� ���
    cout << "���ΰ� : " << player.name << "\n";
    cout << "�̵� : W(��), A(����), S(�Ʒ�), D(������), ����: Q\n";
    cout << "���� ���� �� : " << Bosses << "��\n";
    //�� �� ���� ���� ���
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            if (x == playerX && y == playerY)
                cout << '@'; //�÷��̾� ��ġ, ���
            else
                cout << tiles[y][x]; //���� �⺻ Ÿ�� ��� : ' ', '-', '|'
        }

        //����â ���
        cout << "   "; //���� 3ĭ���� �ʰ� �и�
        if (y == 0)  cout << "==========================";
        if (y == 1) cout << "ü�� : " << player.hp << " / " << player.maxHP << " HP";
        else if (y == 2) cout << "���� : " << player.defense << "%";
        else if (y == 3) cout << "���η� : " << player.attack << "%";
        else if (y == 4) cout << "==========================";
        else if (y == 5) cout << "��� : " << player.getGold();
        else if (y == 6) cout << "==========================";
        else if (y == 7) cout << "�κ��丮";
        else if (y == 8) {
            if (player.isItemPurchased(1)) {
                cout << "����å";
            }
        }
        else if (y == 9) {
            if (player.isItemPurchased(2)) {
                cout << "����";
            }
        }
        else if (y == 10)
        {
            if (player.isItemPurchased(3))
            {
                cout << "�޴���";
            }
        }
        else if (y == 11)
        {
            if (player.getMonsterItemCount() >= 1)
            {
                cout << "���� (" << player.getMonsterItemCount() << " / 5)";
            }
        }
        else if (y == 12) cout << "==========================";
        else if (y == 13) cout << "gpa = " << player.getGPA();
        cout << endl;
    }
}

char Map::getTile(int x, int y) const {
    return tiles[y][x];
}

void Map::setTile(int x, int y, char symbol) {
    tiles[y][x] = symbol;
}
