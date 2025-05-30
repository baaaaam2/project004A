#ifndef PLAYER_H
#define PLAYER_H

#include "Item.h"
#include "Character.h"
#include <string>
#include <vector>

using namespace std;

//�÷��̾� Ŭ���� <= ĳ���� ���
class Player : public Character {
private:
	double gpa = 0; // ����
	int gold; // ���
	int xp; // ����ġ
	int maxXP = 1000; // �ִ� ����ġ
	int level = 1; // ����
	vector<Item> inventory;

	bool itemBookPurchased;
	bool itemCalculatorPurchased;
	bool itemPhonePurchased;
	int itemMonsterPurchased = 0;

	int monsterItemCount = 0;


public:
	Player(string name, int hp, int atk);
	string name;
	string getName() const { return name; } // �̸� ��������

	void setGPA(double newGPA) { gpa = newGPA; }
	void addGPA(double amount) { gpa += amount; } // ������
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

	void levelUp();	// ������

	int getMonsterItemCount() const { return monsterItemCount; }
	void addMonsterItem() { if (monsterItemCount < 5) monsterItemCount++; }

	void useMonsterItem();  // ���� ������ ��� �Լ�

};

#endif
