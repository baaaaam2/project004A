#include "Map.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>

using namespace std;

//맵
Map::Map() {
    initialize();
}
const char game_map[MAP_HEIGHT][MAP_WIDTH + 1] = {
    "+----------------------------+",  // 0
    "|     |        |             |",  // 1 - 오른쪽 위 보스 라벨
    "|     |        |    B        |",  // 2
    "|              +-----------  |",  // 3
    "|                            |",  // 4
    "|                            |",  // 5
    "|     +-----                 |",  // 6
    "|     |                +-----|",  // 7
    "|     +-----           |     |",  // 8
    "|                      |     |",  // 9
    "|                      |     |",   // 10
    "|                            |",  // 11 - 왼쪽 아래 보스 라벨
    "|----------                  |",  // 12
    "|                            |", // 13 - 오른쪽 아래 보스 라벨
    "|     B                      |", // 14
    "|----------                  |",   // 15
    "|                   +--------|",   // 16
    "|    ----+          |        |",   // 17
    "|        |               B   |",   // 18
    "+----------------------------+"  // 19
};


void Map::initialize() 
{
    for (int y = 0; y < MAP_HEIGHT; ++y) {
        for (int x = 0; x < MAP_WIDTH; ++x) {
            tiles[y][x] = game_map[y][x];
        }
    }
}

void Map::print(const Player& player, int playerX, int playerY) {
    system("cls");
    //주인공 이름, 이동방법 출력
    cout << "주인공 : " << player.name << "\n";
    cout << "이동 : W(위), A(왼쪽), S(아래), D(오른쪽), 종료: Q\n";
    //맵 및 현제 상태 출력
    for (int y = 0; y < MAP_HEIGHT; ++y) 
    {
        for (int x = 0; x < MAP_WIDTH; ++x) 
        {
            if (x == playerX && y == playerY)
                cout << '@'; //플레이어 위치, 출력
            else if (y == BOSS_LABEL_Y && x >= BOSS_X - 4 && x < BOSS_X + 4) // 오른쪽 아래 보스 라벨
            {
                cout << "<<boss>>"[x - (BOSS_X - 4)];
            }
            else if (y == BOSS_TOP_Y && x >= BOSS_TOP_X - 4 && x < BOSS_TOP_X + 4) // 오른쪽 위 보스 라벨
            {
                cout << "<<boss>>"[x - (BOSS_TOP_X - 4)];
            }
            else if (y == BOSS_LEFT_Y && x >= BOSS_LEFT_X - 4 && x < BOSS_LEFT_X + 4) // 왼쪽 아래 보스 라벨
            {
                cout << "<<boss>>"[x - (BOSS_LEFT_X - 4)];
            }
            else
                cout << tiles[y][x]; //맵의 기본 타일 출력 : ' ', '-', '|'
        }
        cout << "   "; //공백 3칸으로 맵과 분리
        if (y == 0)  cout << "==========================";
        if (y == 1) cout << "체력 : " << player.hp << " / " << player.maxHP << " HP";
        else if (y == 2) cout << "방어력 : " << player.defense;
        else if (y == 3) cout << "공부력 : " << player.attack;
        else if (y == 4) cout << "==========================";
        else if (y == 5) cout << "인벤토리";
        else if (y == 6) cout << "전공책";
        else if (y == 7) cout << "계산기";
        else if (y == 8) cout << "휴대폰";
        else if (y == 9) cout << "==========================";
        cout << endl;
    }
}

char Map::getTile(int x, int y) const {
    return tiles[y][x];
}

void Map::setTile(int x, int y, char symbol) {
    tiles[y][x] = symbol;
}
