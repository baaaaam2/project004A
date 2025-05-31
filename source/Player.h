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
	double gpa = 0; // 학점
	int gold; // 골드
	int xp; // 경험치
	int maxXP; // 최대 경험치
	int level; // 레벨
	vector<Item> inventory;

	bool itemBookPurchased = false;
	bool itemCalculatorPurchased = false;
	bool itemPhonePurchased = false;
	int itemMonsterPurchased = 0;
	int monsterItemCount = 0;

public:
	Player(string name, int hp, int atk);
	string name;
	string getName() const { return name; } // 이름 가져오기
	void setGPA(double gpa) { this->gpa += gpa; } // 학점 설정
	double averageGPA(int boss) const; // 평균 학점 계산
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
	int getlevel() const; // 현재 레벨 출력
	void addXP(int amount); // 경험치 추가
	int getXP() const; // 현재 경험치 가져오기
	int getMaxXP() const; // 최대 경험치 가져오기

	void useMonsterItem();  // 몬스터 아이템 사용 함수
	int getMonsterItemCount() const; // 몬스터 아이템 개수 가져오기
	void addMonsterItem(); // 몬스터 아이템 추가
};

#endif
