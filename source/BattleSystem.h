#ifndef BOSS_H
#define BOSS_H

#include "Character.h"
#include <string>

using namespace std;

//보스 클래스 <= 캐릭터 상속
class Boss : public Character {
public:
    Boss(const string& name, int maxHP, int attack, int defense);
    string name;

    string getName() const { return name; } // 보스 이름 가져오기
};

#endif
