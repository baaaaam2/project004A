#include "Player.h"

using namespace std;

//플레이어
Player::Player(string name)
    : Character(100, 30, 10), name(move(name)) {
} //체력 100, 공격력 30, 방어력 10
