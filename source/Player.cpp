#include "Player.h"
#include <iostream>
#define PLAYERMAXHP 100

using namespace std;

//플레이어
Player::Player(string name, int hp, int atk)
    : Character(100, 100, 100), name(move(name)), gold(5000),
    itemBookPurchased(false), itemCalculatorPurchased(false), itemPhonePurchased(false)
{
} //체력 100, 공격력 100% = 1, 방어력 100% = 1
//골드 5000 (5천원)

//아이템 구매 상태 
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

//아이템 구매 상태 인식 시키기
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

//아이템 추가
void Player::addItem(const Item& item) {
    inventory.push_back(item);
}

//현 보유 골드 출력
int Player::getGold() const {
    return gold;
}

//골드 추가할때 쓸 것
void Player::addGold(int amount) {
    gold += amount;
}

//체력 회복
void Player::addHp(int amount) {
    hp += amount;
    if (hp >= PLAYERMAXHP)
    {
        hp = PLAYERMAXHP;
    }
}

//공격력 높이기
void Player::addAttackMultiplier(int percent) {
    attack *= percent;
    attack /= 100;
}

//방어력 높이기
void Player::addDefenseMultiplier(int percent) {
    defense *= percent;
    defense /= 100;
}

//레벨 올리기
void Player::levelUp() {
    if (xp >= maxXP) {
        level = level + (xp / maxXP);	// 경험치에 따라 레벨 상승
        xp = xp % maxXP; // 남은 경험치 계산
        hp = maxHP; // 레벨업 시 체력 회복
        cout << name << " 님이 레벨 " << level << "로 상승했습니다!\n";
    }
}

void Player::useMonsterItem() {
    if (monsterItemCount > 0) {
        addHp(30);  // 회복량은 조절 가능
        monsterItemCount--;
        cout << "몬스터 아이템을 사용하여 체력을 회복했습니다!" << endl;
    }
    else {
        cout << "몬스터 아이템이 없습니다." << endl;
    }
}

