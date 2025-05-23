#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include "Player.h"
#include "Boss.h"
#include "Map.h"
#include "BattleSystem.h"
#include "StorySystem.h"

using namespace std;

//컨트롤러 클래스
class Controller {
public:
    Controller(Player& player, vector<Boss> bosses, Map& map);
    void startGame();

private:
    Player& player;
    vector<Boss> bosses;
    Map& map;
    //초기 캐릭터 위치 (1,1)
    int playerX = 1;
    int playerY = 1;

    bool movePlayer(char input);
};

#endif
