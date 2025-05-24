#include "BattleSystem.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>
#define MAX_TURNS 10

using namespace std;

//������(����) ��Ʋ�ý���
void BattleSystem::fight(Player& player, Boss& boss, char& grade) //char& grade �߰�
{
    system("cls");
    char choice;
    int turn = 1;
    bool fighting = true;

    cout << player.getName() << "(��)�� " << boss.getName() << "���� �������� �޾Ҵ�!\n";
    Sleep(1000);
    system("cls");

    while (player.isAlive() && boss.isAlive() && turn <= MAX_TURNS) 
    {
        // ��� ���� ���
        cout << boss.getName() << " : �� ������ Ǯ�����!\n";

        cout << "======= ���� ȭ�� ======\n";
        cout << "[���� ���� �ð� " << turn << " / " << MAX_TURNS << "]\n";

        printStatus(player, boss);

        // �ൿ ����
        cout << "1. ���� Ǯ��\n";
        cout << "2. ������ ��� (�̱���)\n����: ";
        cin >> choice;

        if (choice == '1') {
            char atkChoice;
            cout << "\n� ������ ����ұ��?\n";
            cout << "1. Ǯ�� (30 ������, 70% ����)\n";
            cout << "2. ��� (50 ������, 50% ����)\n";
            cout << "3. �����ϱ� (70 ������, 30% ����)\n";
            cout << "����: ";
            cin >> atkChoice;

            int damage = 0, successRate = 0;
            switch (atkChoice) {
            case '1': damage = 30; successRate = 70; break;
            case '2': damage = 50; successRate = 50; break;
            case '3': damage = 70; successRate = 30; break;
            default: continue;
            }
            // ���� ����
            system("cls");
            printStatus(player, boss);
            attack(player, boss, damage, successRate, "���ΰ�", "������");

            if (boss.isDead()) {
                cout << "\n====================\n";
                cout << "�������� �� Ǯ�����ϴ�!\n";
                cout << "====================\n";
                if (player.hp >= 70) grade = 'A'; // ü�� 70 �̻�: A����
                else if (player.hp > 0) grade = 'B'; // ü�� 1~69: B����
                fighting = false;
                continue;
            }

            attack(boss, player, 30, 70, "����", "���ΰ�");

            if (player.isDead()) {
                system("cls");
                cout << "\n====================\n";
                cout << "������ �� Ǯ�� ���߽��ϴ�! ���� ����!\n";
                cout << "====================\n";
                grade = 'C'; // �й�: C����
                fighting = false;
            }
        }
        else if(choice == '2')
        {
            cout << "������ ����� ���� �������� �ʾҽ��ϴ�.\n";
            Sleep(1500); //1.5�� ����
        }
        else if (choice != 2 || choice != 1)
        {
            cout << "�˸��� �ɼ��� �������ּ���.\n";
            Sleep(1500);
        }

        // �ൿ �� ȭ�� ���� (HP�� ����)
        if (fighting)
        {
            system("cls");
        }
        turn++;
    }
}

//ģ��(�߰�����) ��Ʋ�ý���
void BattleSystem::fightfriend(Player& player, Boss& boss)
{
    system("cls");
    char choice;
    bool fighting = true;

    std::cout << player.getName() << "(��)�� " << boss.getName() << "���� ������ �޾Ҵ�!\n";
    Sleep(1000);

    while (fighting) {
        std::cout << boss.getName() << " : �̰� ��� Ǯ��?\n" << std::endl;
        printStatus(player, boss);
        std::cout << "1. ���� Ǯ��\n";
        std::cout << "2. ������ ��� (�̱���)\n����: ";
        std::cin >> choice;
        if (choice == '1') {
            char atkChoice;
            std::cout << "1. Ǯ�� (30, 70%)\n2. ��� (50, 50%)\n3. ���� (70, 30%)\n����: ";
            std::cin >> atkChoice;
            int damage = 0, successRate = 0;
            switch (atkChoice) {
            case '1': damage = 30; successRate = 70; break;
            case '2': damage = 50; successRate = 50; break;
            case '3': damage = 70; successRate = 30; break;
            default: continue;
            }
            system("cls");
            printStatus(player, boss);
            attack(player, boss, damage, successRate, "���ΰ�", "ģ��");
            if (boss.isDead()) {
                std::cout << "�������� �� Ǯ�����ϴ�!\n";
                fighting = false;
                continue;
            }
            attack(boss, player, 30, 70, "����", "���ΰ�");
            if (player.isDead()) {
                std::cout << "������ �� Ǯ�� ���߽��ϴ�! ���� ����!\n";
                fighting = false;
            }
        }
        else {
            std::cout << "������ ����� ���� �������� �ʾҽ��ϴ�.\n";
            Sleep(1500);
        }
        if (fighting) system("cls");
    }
}

void BattleSystem::attack(Character& attacker, Character& defender, int damage, int successRate, const string& attackerName, const string& defenderName) {
    cout << attackerName << "�� ����!\n";
    if (isAttackSuccessful(successRate)) {
        defender.takeDamage(damage);
        cout << "���� ����! " << defenderName << "���� " << damage << " ����!\n";
    }
    else {
        cout << "���� ����!\n";
    }
    Sleep(1000); //1�� ����
}

bool BattleSystem::isAttackSuccessful(int successRate) {
    return rand() % 100 < successRate;
}

void BattleSystem::printStatus(const Player& player, const Boss& boss) {
    cout << "====================\n";
    cout << "�÷��̾� : " << player.hp << " / " << player.maxHP << " HP\n";
    cout << "������ : " << boss.hp << " / " << boss.maxHP << " HP\n";
    cout << "====================\n\n";
}
