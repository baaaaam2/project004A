#ifndef MAP_H
#define MAP_H

#include "Player.h"
using namespace std;


const int MAP_WIDTH = 30; //맵 X축 크기
const int MAP_HEIGHT = 20; //맵 Y축 크기
const int BOSS_X = MAP_WIDTH - 5; //보스 X축 위치
const int BOSS_Y = MAP_HEIGHT - 2; //보스 Y축 위치
const int BOSS_LABEL_Y = MAP_HEIGHT - 3; //보스 라벨 위치


//여기부터
const int BOSS_TOP_X = MAP_WIDTH - 10;  // 오른쪽 위 보스 X 위치 (적당히 조정)
const int BOSS_TOP_Y = 1;               // 오른쪽 위 보스 라벨 Y 위치

// 추가: 왼쪽 아래 보스 위치
const int BOSS_LEFT_X = 6;              // 왼쪽 아래 보스 X 위치
const int BOSS_LEFT_Y = MAP_HEIGHT - 7; // 왼쪽 아래 보스 라벨 Y 위치
//여기까지 추가


//맵 클래스
class Map {
public:
    Map();
    void initialize();
    void print(const Player& player, int playerX, int playerY);
    char getTile(int x, int y) const;
    void setTile(int x, int y, char symbol);

private:
    char tiles[MAP_HEIGHT][MAP_WIDTH];
};

#endif
