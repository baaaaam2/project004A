#ifndef BATTLESYSTEM_H
#define BATTLESYSTEM_H

#include "Player.h"
#include "Boss.h"
#include <string>

//배틀시스템 클래스
using namespace std;

class BattleSystem {
public:
    void fight(Player& player, Boss& boss, char& grade);// 수정: grade 추가

private:
    void attack(Character& attacker, Character& defender, int damage, int successRate, const string& attackerName, const string& defenderName);
    bool isAttackSuccessful(int successRate);
    void printStatus(const Player& player, const Boss& boss);
};

#endif
