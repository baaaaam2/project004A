#include "Skill.h"

Skill::Skill(std::string name, int damage, int successRate)
    : name(name), damage(damage), successRate(successRate) {}

std::string Skill::getName() const { return name; }
int Skill::getDamage() const { return damage; }
int Skill::getSuccessRate() const { return successRate; }

int Skill::calculateDamage(int playerAttackPercent) const // 플레이어 공격력에 따른 스킬 데미지 계산 추가
{
    return damage * playerAttackPercent / 100;
}