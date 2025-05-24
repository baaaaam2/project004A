#ifndef BOSS_H
#define BOSS_H

#include "Character.h"
#include <string>

using namespace std;

//���� Ŭ���� <= ĳ���� ���
class Boss : public Character {
public:
    Boss(const string& name, int maxHP, int attack, int defense);
    string name;

    string getName() const { return name; } // ���� �̸� ��������
};

#endif
