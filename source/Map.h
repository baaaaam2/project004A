#ifndef MAP_H
#define MAP_H

#include "Player.h"

const int MAP_WIDTH = 30; //맵 X축 크기
const int MAP_HEIGHT = 20; //맵 Y축 크기
const int BOSS_X = MAP_WIDTH - 5; //보스 X축 위치
const int BOSS_Y = MAP_HEIGHT - 2; //보스 Y축 위치
const int BOSS_LABEL_Y = MAP_HEIGHT - 3; //보스 라벨 위치
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
