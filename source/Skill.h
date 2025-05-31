#ifndef SKILL_H
#define SKILL_H

#include <string>

class Skill {
public:
    Skill(std::string name, int damage, int successRate);

	std::string getName() const; // ��ų �̸� ��ȯ
	int calculateDamage(int playerAttackPercent) const; // �÷��̾� ���ݷ¿� ���� ��ų ������ ���
	int getDamage() const; // ��ų ������ ��ȯ
	int getSuccessRate() const; // ��ų ������ ��ȯ

private:
    std::string name;
    int damage;
    int successRate;
};

#endif