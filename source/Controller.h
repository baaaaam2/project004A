#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Player.h"
#include "Boss.h"
#include "Map.h"
//컨트롤러 클래스(키보드 인식 -> 움직임)
class Controller {
public:
    Controller(Player& player, Boss& boss, Map& map);
    void startGame();

private:
    Player& player;
    Boss& boss;
    Map& map;
    //초기 캐릭터 위치 (1,1)
    int playerX = 1;
    int playerY = 1;

    bool movePlayer(char input);
};

#endif
