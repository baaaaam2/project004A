#include "Player.h"
//�÷��̾�
Player::Player(std::string name)
    : Character(100, 30, 10), name(std::move(name)) {
} //ü�� 100, ���ݷ� 30, ���� 10
