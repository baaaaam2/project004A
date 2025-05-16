#ifndef CHARACTER_H
#define CHARACTER_H
//ĳ���� Ŭ����
class Character {
public:
    Character(int maxHP, int attack, int defense);
    virtual ~Character() = default;

    virtual void takeDamage(int amount);
    bool isDead() const;

    int maxHP; //�ִ�ü��
    int hp; //����ü��
    int attack; //���ݷ�
    int defense; //����
};

#endif
