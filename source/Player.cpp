#include "Player.h"
#include <iostream>
#define PLAYERMAXHP 100

using namespace std;

//�÷��̾�
Player::Player(string name, int hp, int atk)
    : Character(100, 100, 100), name(move(name)), gold(5000), xp(0), maxXP(1000), level(1), gpa(0),
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
	default:
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

//���� �ø���
void Player::levelUp() {
    if (xp >= maxXP) {
        level = level + (xp / maxXP);	// ����ġ�� ���� ���� ���
        xp = xp % maxXP; // ���� ����ġ ���
        maxHP += 20; // ������ �� �ִ� ü�� ����
        hp = maxHP; // ������ �� ü�� ȸ��
        cout << name << " ���� ���� " << level << "�� ����߽��ϴ�!\n";
    }
}

//���� ���� ���
int Player::getlevel() const {
	return level;
}

// ����ġ �߰�
void Player::addXP(int amount) {
	xp += amount;
	levelUp(); // ����ġ �߰� �� ������ üũ
}

// ���� ����ġ ��������
int Player::getXP() const {
	return xp;
}

// �ִ� ����ġ ��������
int Player::getMaxXP() const {
	return maxXP;
}

//��� ���� ���
double Player::averageGPA(int boss) const {
    double avegpa = gpa / (3 - boss); // 3���� ��� ����
    if (gpa == 0)
    {
        return gpa;
    }
	if (avegpa < 0.0) avegpa = 0.0; // ���� ����
	return avegpa;
}

// ���� ������ ���
void Player::useMonsterItem() {
    if (monsterItemCount > 0) {
        addHp(30);  // ȸ������ ���� ����
        monsterItemCount--;
        cout << "���� �������� ����Ͽ� ü���� ȸ���߽��ϴ�!" << endl;
    }
    else {
        cout << "���� �������� �����ϴ�." << endl;
    }
}

// ���� ������ ���� ��������
int Player::getMonsterItemCount() const {
	return monsterItemCount;
}

// ���� ������ �߰�
void Player::addMonsterItem() {
    if (monsterItemCount < 5) monsterItemCount++;
}
