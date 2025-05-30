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

//컨트롤러 클래스
class Controller {
public:
    Controller(Player& player, vector<Boss> bosses, Map& map);
    void startGame();
private:
    Player& player;
    vector<Boss> bosses;
    vector<bool> defeatedBosses; // 보스 전투 결과 저장
    map<pair<int, int>, int> bossMap; // 보스 위치와 인덱스 매핑
    Map& map;
    //초기 캐릭터 위치 (1,1)
    int playerX = 1;
    int playerY = 1;

    bool movePlayer(char input);
    int getRemainingBossCount() const; // 남은 보스 수 반환
};

#endif

