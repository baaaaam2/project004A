#include "Skill.h"

Skill::Skill(std::string name, int damage, int successRate)
    : name(name), damage(damage), successRate(successRate) {}

std::string Skill::getName() const { return name; }
int Skill::getDamage() const { return damage; }
int Skill::getSuccessRate() const { return successRate; }
