#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include "Player.h"
#include "Boss.h"
#include "Map.h"
#include "BattleSystem.h"
#include "StorySystem.h"

using namespace std;

//��Ʈ�ѷ� Ŭ����
class Controller {
public:
    Controller(Player& player, vector<Boss> bosses, Map& map);
    void startGame();

private:
    Player& player;
    vector<Boss> bosses;
    Map& map;
    //�ʱ� ĳ���� ��ġ (1,1)
    int playerX = 1;
    int playerY = 1;

    bool movePlayer(char input);
};

#endif
