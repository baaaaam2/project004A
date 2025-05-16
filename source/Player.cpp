#include "Player.h"
//플레이어
Player::Player(std::string name)
    : Character(100, 30, 10), name(std::move(name)) {
} //체력 100, 공격력 30, 방어력 10
