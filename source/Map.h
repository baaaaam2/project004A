#ifndef MAP_H
#define MAP_H

#include "Player.h"
using namespace std;


const int MAP_WIDTH = 30; //�� X�� ũ��
const int MAP_HEIGHT = 20; //�� Y�� ũ��
const int BOSS_X = MAP_WIDTH - 5; //���� X�� ��ġ
const int BOSS_Y = MAP_HEIGHT - 2; //���� Y�� ��ġ
const int BOSS_LABEL_Y = MAP_HEIGHT - 3; //���� �� ��ġ


//�������
const int BOSS_TOP_X = MAP_WIDTH - 10;  // ������ �� ���� X ��ġ (������ ����)
const int BOSS_TOP_Y = 1;               // ������ �� ���� �� Y ��ġ

// �߰�: ���� �Ʒ� ���� ��ġ
const int BOSS_LEFT_X = 6;              // ���� �Ʒ� ���� X ��ġ
const int BOSS_LEFT_Y = MAP_HEIGHT - 7; // ���� �Ʒ� ���� �� Y ��ġ
//������� �߰�


//�� Ŭ����
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
