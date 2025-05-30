#ifndef PLAYER_H
#define PLAYER_H

#include "Item.h"
#include "Character.h"
#include <string>
#include <vector>

using namespace std;

//플레이어 클래스 <= 캐릭터 상속
class Player : public Character {
private:
	double gpa = 0; // 학점
	int gold; // 골드
	int xp; // 경험치
	int maxXP = 1000; // 최대 경험치
	int level = 1; // 레벨
	vector<Item> inventory;

	bool itemBookPurchased;
	bool itemCalculatorPurchased;
	bool itemPhonePurchased;
	int itemMonsterPurchased = 0;

	int monsterItemCount = 0;


public:
	Player(string name, int hp, int atk);
	string name;
	string getName() const { return name; } // 이름 가져오기

	void setGPA(double newGPA) { gpa = newGPA; }
	void addGPA(double amount) { gpa += amount; } // 누적용
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

	void levelUp();	// 레벨업

	int getMonsterItemCount() const { return monsterItemCount; }
	void addMonsterItem() { if (monsterItemCount < 5) monsterItemCount++; }

	void useMonsterItem();  // 몬스터 아이템 사용 함수

};

#endif
