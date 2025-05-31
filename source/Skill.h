#ifndef SKILL_H
#define SKILL_H

#include <string>

class Skill {
public:
    Skill(std::string name, int damage, int successRate);

	std::string getName() const; // 스킬 이름 반환
	int calculateDamage(int playerAttackPercent) const; // 플레이어 공격력에 따른 스킬 데미지 계산
	int getDamage() const; // 스킬 데미지 반환
	int getSuccessRate() const; // 스킬 성공률 반환

private:
    std::string name;
    int damage;
    int successRate;
};

#endif