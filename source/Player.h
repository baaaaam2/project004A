#ifndef PLAYER_H
#define PLAYER_H

using namespace std;

#include <string>
#include "Character.h"
//플레이어 클래스 <= 캐릭터 상속
class Player : public Character {
public:
    Player(string name);
    string name;
};

#endif
