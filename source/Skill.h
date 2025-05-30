#ifndef SKILL_H
#define SKILL_H

#include <string>

class Skill {
public:
    Skill(std::string name, int damage, int successRate);

    std::string getName() const;
    int getDamage() const;
    int getSuccessRate() const;

private:
    std::string name;
    int damage;
    int successRate;
};

#endif