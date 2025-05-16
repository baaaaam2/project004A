#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Character.h"
//플레이어 클래스 <= 캐릭터 상속
class Player : public Character {
public:
    Player(std::string name);
    std::string name;
};

#endif
