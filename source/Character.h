#ifndef CHARACTER_H
#define CHARACTER_H
//ĳ���� Ŭ����
using namespace std;

class Character {
public:
    Character(int maxHP, int attack, int defense);
    virtual ~Character() = default;

    virtual void takeDamage(int amount);

    bool isAlive() const;
    bool isDead() const;

    int maxHP; //�ִ�ü��
    int hp; //����ü��
    int attack; //���ݷ�
    int defense; //����
};

#endif
