#include "Player.h"
#include <iostream>

using namespace std;

//�÷��̾�
Player::Player(string name, int hp, int atk)
    : Character(100, 30, 10), name(move(name)), gold(50){
} //ü�� 100, ���ݷ� 30, ���� 10

void Player::showStatus() const {
    cout << "[�÷��̾� ����] " << name << " | HP: " << hp << " | ���ݷ�: " << attack << " | ���: " << gold << "\n";
}

void Player::addItem(const Item& item) {
    inventory.push_back(item);
}

void Player::showInventory() const {
    cout << "\n[�κ��丮 ���]\n";
    for (size_t i = 0; i < inventory.size(); ++i) {
        cout << i + 1 << ". " << inventory[i].getName()
            << " (ȸ����: " << inventory[i].getHealAmount() << ")\n";
    }
    if (inventory.empty()) cout << "������ ����.\n";
}

int Player::getGold() const {
    return gold;
}

void Player::addGold(int amount) {
    gold += amount;
}

void Player::useItem(int index) {
    if (index < 1 || index > inventory.size()) {
        cout << "�߸��� �����Դϴ�.\n";
        return;
    }

    Item item = inventory[index - 1];
    hp += item.getHealAmount();
    if (hp > maxHP) hp = maxHP;
    std::cout << item.getName() << " ��(��) ����߽��ϴ�. HP�� " << item.getHealAmount() << " ȸ���˴ϴ�.\n";
    inventory.erase(inventory.begin() + index - 1);
}
