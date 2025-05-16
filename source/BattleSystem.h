#ifndef BATTLESYSTEM_H
#define BATTLESYSTEM_H

#include "Player.h"
#include "Boss.h"
//��Ʋ�ý��� Ŭ����
class BattleSystem {
public:
    void fight(Player& player, Boss& boss);

private:
    void attack(Character& attacker, Character& defender, int damage, int successRate, const std::string& attackerName, const std::string& defenderName);
    bool isAttackSuccessful(int successRate);
    void printStatus(const Player& player, const Boss& boss);
};

#endif
