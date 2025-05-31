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
	double gpa = 0; // ����
	int gold; // ���
	int xp; // ����ġ
	int maxXP; // �ִ� ����ġ
	int level; // ����
	vector<Item> inventory;

	bool itemBookPurchased = false;
	bool itemCalculatorPurchased = false;
	bool itemPhonePurchased = false;
	int itemMonsterPurchased = 0;
	int monsterItemCount = 0;

public:
	Player(string name, int hp, int atk);
	string name;
	string getName() const { return name; } // �̸� ��������
	void setGPA(double gpa) { this->gpa += gpa; } // ���� ����
	double averageGPA(int boss) const; // ��� ���� ���
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
	int getlevel() const; // ���� ���� ���
	void addXP(int amount); // ����ġ �߰�
	int getXP() const; // ���� ����ġ ��������
	int getMaxXP() const; // �ִ� ����ġ ��������

	void useMonsterItem();  // ���� ������ ��� �Լ�
	int getMonsterItemCount() const; // ���� ������ ���� ��������
	void addMonsterItem(); // ���� ������ �߰�
};

#endif
