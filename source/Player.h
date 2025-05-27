#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Item.h"
#include "Character.h"
#include <vector>

using namespace std;

//�÷��̾� Ŭ���� <= ĳ���� ���
class Player : public Character {
private:
	double gpa; // ����
	int gold; // ���
	vector<Item> inventory;

	bool itemBookPurchased;
	bool itemCalculatorPurchased;
	bool itemPhonePurchased;

public:
	Player(string name, int hp, int atk);
	string name;
	string getName() const { return name; } // �̸� ��������
	void setGPA(int gpa) { this->gpa = gpa; } // ���� ����
	double getGPA() const { return gpa; } // ���� ��������
	bool isAlive() const { return hp > 0; } // ���� ���� Ȯ��
	bool isDead() const { return hp <= 0; } // ��� ���� Ȯ��

	void showStatus() const;
	void addItem(const Item& item);
	void showInventory() const;
	int getGold() const; // ���� ��� �� ���
	void addGold(int amount); // ��� �� +

	void addHp(int amount);
	bool isItemPurchased(int itemId) const;
	void purchaseItem(int itemId);

	void addAttackMultiplier(int percent);  // ��: 120 �� 1.2��
	void addDefenseMultiplier(int percent);  // ��: 120 �� 1.2��
};

#endif
