#include "Map.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>
//��
Map::Map() {
    initialize();
}

void Map::initialize() 
{
    //���� ' '���� �ʱ�ȭ
    for (int y = 0; y < MAP_HEIGHT; ++y)
        for (int x = 0; x < MAP_WIDTH; ++x)
            tiles[y][x] = ' ';
    //���, �ϴ� ���
    for (int x = 0; x < MAP_WIDTH; ++x)
        tiles[0][x] = tiles[MAP_HEIGHT - 1][x] = (x == 0 || x == MAP_WIDTH - 1) ? '|' : '-';
    //����, ���� ���
    for (int y = 1; y < MAP_HEIGHT - 1; ++y) {
        tiles[y][0] = '|';
        tiles[y][MAP_WIDTH - 1] = '|';
    }
    //���� ��ġ
    tiles[BOSS_Y][BOSS_X] = 'P';
}

void Map::print(const Player& player, int playerX, int playerY) {
    system("cls");
    //���ΰ� �̸�, �̵���� ���
    std::cout << "���ΰ� : " << player.name << "\n";
    std::cout << "�̵� : W(��), A(����), S(�Ʒ�), D(������), ����: Q\n";
    //�� �� ���� ���� ���
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            if (x == playerX && y == playerY)
                std::cout << '@'; //�÷��̾� ��ġ, ���
            else if (y == BOSS_LABEL_Y && x >= BOSS_X - 4 && x < BOSS_X + 4) //���� ��ġ, ���
                std::cout << "<<boss>>"[x - (BOSS_X - 4)]; //���� �� ��ġ, ���
            else
                std::cout << tiles[y][x]; //���� �⺻ Ÿ�� ��� : ' ', '-', '|'
        }
        std::cout << "   "; //���� 3ĭ���� �ʰ� �и�
        if (y == 0)  std::cout << "==========================";
        if (y == 1) std::cout << "ü�� : " << player.hp << " / " << player.maxHP << " HP";
        else if (y == 2) std::cout << "���� : " << player.defense;
        else if (y == 3) std::cout << "���η� : " << player.attack;
        else if (y == 4) std::cout << "==========================";
        else if (y == 5) std::cout << "�κ��丮";
        else if (y == 6) std::cout << "����å";
        else if (y == 7) std::cout << "����";
        else if (y == 8) std::cout << "�޴���";
        else if (y == 9) std::cout << "==========================";
        std::cout << std::endl;
    }
}

char Map::getTile(int x, int y) const {
    return tiles[y][x];
}

void Map::setTile(int x, int y, char symbol) {
    tiles[y][x] = symbol;
}
