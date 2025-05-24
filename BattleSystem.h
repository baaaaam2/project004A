#ifndef BATTLESYSTEM_H
#define BATTLESYSTEM_H

#include "Player.h"
#include "Boss.h"
#include <string>

//��Ʋ�ý��� Ŭ����
using namespace std;

class BattleSystem {
public:
    void fight(Player& player, Boss& boss, char& grade);// ������ ��������
    void fightfriend(Player& player, Boss& boss); // ģ��(�߰�����)���� ���� ����

private:
    void attack(Character& attacker, Character& defender, int damage, int successRate, const string& attackerName, const string& defenderName);
    bool isAttackSuccessful(int successRate); //���� ���� ���� �Ǵ�
    void printStatus(const Player& player, const Boss& boss); //���� ���
};

#endif
