#include "Character.h"
//ĳ����
Character::Character(int maxHP, int attack, int defense)
    : maxHP(maxHP), hp(maxHP), attack(attack), defense(defense) {
}
//�������� �޴� �Լ�
void Character::takeDamage(int amount) {
    hp -= amount;
    if (hp < 0) hp = 0;
}
//���� ����
bool Character::isDead() const {
    return hp <= 0;
}
