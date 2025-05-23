#ifndef CHARACTER_H
#define CHARACTER_H
//캐릭터 클래스
using namespace std;

class Character {
public:
    Character(int maxHP, int attack, int defense);
    virtual ~Character() = default;

    virtual void takeDamage(int amount);
    void attacking(Character& target) {
        int damage = attack - target.defense;
        if (damage < 0) damage = 0;
        target.takeDamage(damage);
    }

    bool isAlive() const;
    bool isDead() const;

    int maxHP; //최대체력
    int hp; //현제체력
    int attack; //공격력
    int defense; //방어력
};

#endif
