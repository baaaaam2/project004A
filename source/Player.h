#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Character.h"
//�÷��̾� Ŭ���� <= ĳ���� ���
class Player : public Character {
public:
    Player(std::string name);
    std::string name;
};

#endif
