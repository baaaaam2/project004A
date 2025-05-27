#include "Player.h"
#include <iostream>
#define PLAYERMAXHP 100

using namespace std;

//�÷��̾�
Player::Player(string name, int hp, int atk)
    : Character(100, 100, 100), name(move(name)), gold(5000),
    itemBookPurchased(false), itemCalculatorPurchased(false), itemPhonePurchased(false)
{
} //ü�� 100, ���ݷ� 100% = 1, ���� 100% = 1
//��� 5000 (5õ��)

//������ ���� ���� 
bool Player::isItemPurchased(int item) const {
    switch (item) 
    {
    case 1: 
        return itemBookPurchased;
    case 2: 
        return itemCalculatorPurchased;
    case 3: 
        return itemPhonePurchased;
    default: 
        return false;
    }
}

//������ ���� ���� �ν� ��Ű��
void Player::purchaseItem(int item) {
    switch (item) 
    {
    case 1: 
        itemBookPurchased = true; 
        break;
    case 2: 
        itemCalculatorPurchased = true; 
        break;
    case 3: 
        itemPhonePurchased = true; 
        break;
    }
}

//������ �߰�
void Player::addItem(const Item& item) {
    inventory.push_back(item);
}

//�� ���� ��� ���
int Player::getGold() const {
    return gold;
}

//��� �߰��Ҷ� �� ��
void Player::addGold(int amount) {
    gold += amount;
}

//ü�� ȸ��
void Player::addHp(int amount) {
    hp += amount;
    if (hp >= PLAYERMAXHP)
    {
        hp = PLAYERMAXHP;
    }
}

//���ݷ� ���̱�
void Player::addAttackMultiplier(int percent) {
    attack *= percent;
    attack /= 100;
}

//���� ���̱�
void Player::addDefenseMultiplier(int percent) {
    defense *= percent;
    defense /= 100;
}
