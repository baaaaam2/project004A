#include "Player.h"
#include <iostream>

using namespace std;

//플레이어
Player::Player(string name, int hp, int atk)
    : Character(100, 30, 10), name(move(name)), gold(50){
} //체력 100, 공격력 30, 방어력 10

void Player::showStatus() const {
    cout << "[플레이어 정보] " << name << " | HP: " << hp << " | 공격력: " << attack << " | 골드: " << gold << "\n";
}

void Player::addItem(const Item& item) {
    inventory.push_back(item);
}

void Player::showInventory() const {
    cout << "\n[인벤토리 목록]\n";
    for (size_t i = 0; i < inventory.size(); ++i) {
        cout << i + 1 << ". " << inventory[i].getName()
            << " (회복량: " << inventory[i].getHealAmount() << ")\n";
    }
    if (inventory.empty()) cout << "아이템 없음.\n";
}

int Player::getGold() const {
    return gold;
}

void Player::addGold(int amount) {
    gold += amount;
}

void Player::useItem(int index) {
    if (index < 1 || index > inventory.size()) {
        cout << "잘못된 선택입니다.\n";
        return;
    }

    Item item = inventory[index - 1];
    hp += item.getHealAmount();
    if (hp > maxHP) hp = maxHP;
    std::cout << item.getName() << " 을(를) 사용했습니다. HP가 " << item.getHealAmount() << " 회복됩니다.\n";
    inventory.erase(inventory.begin() + index - 1);
}
