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
	int credit; // 크레딧
	double gpa; // 학점
	int gold;
	vector<Item> inventory;
public:
	Player(string name, int hp, int atk);
	string name;

	string getName() const { return name; } // 이름 가져오기
	void setCredit(int credit) { this->credit = credit; } // 크레딧 설정
	int getCredit() const { return credit; } // 크레딧 가져오기
	void setGPA(int gpa) { this->gpa = gpa; } // 학점 설정
	double getGPA() const { return gpa; } // 학점 가져오기
	bool isAlive() const { return hp > 0; } // 생존 여부 확인
	bool isDead() const { return hp <= 0; } // 사망 여부 확인

	void showStatus() const;
	void addItem(const Item& item);
	void showInventory() const;
	int getGold() const;
	void addGold(int amount);
	void useItem(int index);
};

#endif
