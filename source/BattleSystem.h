#ifndef BATTLESYSTEM_H
#define BATTLESYSTEM_H

#include "Player.h"
#include "Boss.h"
#include <string>

//배틀시스템 클래스
using namespace std;

class BattleSystem {
public:
    void fight(Player& player, Boss& boss, char& grade);// 보스와 전투시작
    void fightfriend(Player& player, Boss& boss); // 친구(중간보스)와의 전투 시작

private:
    void attack(Character& attacker, Character& defender, int damage, int successRate, const string& attackerName, const string& defenderName);
    bool isAttackSuccessful(int successRate); //공격 성공 여부 판단
    void printStatus(const Player& player, const Boss& boss); //상태 출력
};

#endif
