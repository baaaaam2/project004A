#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <vector>
#include <map>
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
    vector<bool> defeatedBosses; // ���� ���� ��� ����
    map<pair<int, int>, int> bossMap; // ���� ��ġ�� �ε��� ����
    Map& map;
    //�ʱ� ĳ���� ��ġ (1,1)
    int playerX = 1;
    int playerY = 1;

    bool movePlayer(char input);
    int getRemainingBossCount() const; // ���� ���� �� ��ȯ
};

#endif

