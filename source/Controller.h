#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Player.h"
#include "Boss.h"
#include "Map.h"
//��Ʈ�ѷ� Ŭ����(Ű���� �ν� -> ������)
class Controller {
public:
    Controller(Player& player, Boss& boss, Map& map);
    void startGame();

private:
    Player& player;
    Boss& boss;
    Map& map;
    //�ʱ� ĳ���� ��ġ (1,1)
    int playerX = 1;
    int playerY = 1;

    bool movePlayer(char input);
};

#endif
