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
	int credit; // ũ����
	double gpa; // ����
	int gold;
	vector<Item> inventory;
public:
	Player(string name, int hp, int atk);
	string name;

	string getName() const { return name; } // �̸� ��������
	void setCredit(int credit) { this->credit = credit; } // ũ���� ����
	int getCredit() const { return credit; } // ũ���� ��������
	void setGPA(int gpa) { this->gpa = gpa; } // ���� ����
	double getGPA() const { return gpa; } // ���� ��������
	bool isAlive() const { return hp > 0; } // ���� ���� Ȯ��
	bool isDead() const { return hp <= 0; } // ��� ���� Ȯ��

	void showStatus() const;
	void addItem(const Item& item);
	void showInventory() const;
	int getGold() const;
	void addGold(int amount);
	void useItem(int index);
};

#endif
