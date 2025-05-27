#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Item.h"
#include "Character.h"
#include <vector>

using namespace std;

//플레이어 클래스 <= 캐릭터 상속
class Player : public Character {
private:
	double gpa; // 학점
	int gold; // 골드
	vector<Item> inventory;

	bool itemBookPurchased;
	bool itemCalculatorPurchased;
	bool itemPhonePurchased;

public:
	Player(string name, int hp, int atk);
	string name;
	string getName() const { return name; } // 이름 가져오기
	void setGPA(int gpa) { this->gpa = gpa; } // 학점 설정
	double getGPA() const { return gpa; } // 학점 가져오기
	bool isAlive() const { return hp > 0; } // 생존 여부 확인
	bool isDead() const { return hp <= 0; } // 사망 여부 확인

	void showStatus() const;
	void addItem(const Item& item);
	void showInventory() const;
	int getGold() const; // 현재 골드 값 출력
	void addGold(int amount); // 골드 값 +

	void addHp(int amount);
	bool isItemPurchased(int itemId) const;
	void purchaseItem(int itemId);

	void addAttackMultiplier(int percent);  // 예: 120 → 1.2배
	void addDefenseMultiplier(int percent);  // 예: 120 → 1.2배
};

#endif
