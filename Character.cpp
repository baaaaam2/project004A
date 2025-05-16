#include "Character.h"
//캐릭터
Character::Character(int maxHP, int attack, int defense)
    : maxHP(maxHP), hp(maxHP), attack(attack), defense(defense) {
}
//데미지를 받는 함수
void Character::takeDamage(int amount) {
    hp -= amount;
    if (hp < 0) hp = 0;
}
//죽음 감지
bool Character::isDead() const {
    return hp <= 0;
}
