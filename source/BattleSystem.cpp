#include "BattleSystem.h"
#include "Skill.h"
#include "StorySystem.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <iomanip>

using namespace std;

//������(����) ��Ʋ�ý���
void BattleSystem::fight(Player& player, Boss& boss, double& gpa) //gpa = ���� �ý���
{
    double earnedGPA = 0.0;
    system("cls");
    char choice;
    bool fighting = true;

    cout << player.getName() << "(��)�� " << boss.getName() << "���� �������� �޾Ҵ�!\n";
    Sleep(1000);
    system("cls");

    // ��ų ����
    Skill skill2("���", 50, 50);
    Skill skill3("����", 70, 100);

    while (fighting)
    {
        // ��� ���� ���
        cout << boss.getName() << " : �� ������ Ǯ�����!\n";

        cout << "======== ���� ȭ�� ========\n";

        printStatus(player, boss);

        // �ൿ ����
        cout << "1. ���� Ǯ��\n";
        cout << "2. ������ ���\n";
        cout << "����: ";
        cin >> choice;

        if (choice == '1') {
            char atkChoice;
            cout << "\n� ������ ����ұ��?\n";
            cout << "1. ��Ÿ (10 ������, 100% ����)\n";
            cout << "2. " << skill2.getName() << " (" << skill2.getDamage() << " ������, " << skill2.getSuccessRate() << "% ����)\n";
            cout << "3. " << skill3.getName() << " (" << skill3.getDamage() << " ������, " << skill3.getSuccessRate() << "% ����)\n";
            cout << "����: ";
            cin >> atkChoice;

            int damage = 0, successRate = 0;
            switch (atkChoice) {
            case '1':
                damage = 10;
                successRate = 100;
                break;
            case '2':
                damage = skill2.getDamage();
                successRate = skill2.getSuccessRate();
                break;
            case '3':
                damage = skill3.getDamage();
                successRate = skill3.getSuccessRate();
                break;
            default:
                cout << "�߸��� �Է��Դϴ�.\n";
                Sleep(1000);
                continue;
            }

            // ���� ����
            system("cls");
            printStatus(player, boss);
            attack(player, boss, damage, successRate, player.getName(), boss.getName());

            if (boss.isDead()) {
                cout << "\n====================\n";
                cout << "�������� �� Ǯ�����ϴ�!\n";
                cout << "====================\n";
                if (player.hp >= 70) // 70 �̻�
                {
                    cout << "������ �� �¾� A������ �¾ҽ��ϴ�!\n\n";
                    earnedGPA += 4.0;
                    Sleep(1500);
                }
                else if (player.hp >= 40)  // 40 �̻� 70 �̸�
                {
                    cout << "��� ������ Ʋ�� B������ �¾ҽ��ϴ�!\n\n";
                    earnedGPA += 3.0;
                    Sleep(1500);
                }
                else if (player.hp > 0)    // 1 �̻� 39 ����
                {
                    cout << "���� ������ Ʋ�� C������ �¾ҽ��ϴ�!\n\n";
                    earnedGPA += 2.0;
                    Sleep(1500);
                }
                printWinStory(player);
                player.addGPA(earnedGPA); // ���� ����
                fighting = false;
                continue;
            }

            attack(boss, player, boss.attack, 70, boss.getName(), player.getName());

            if (player.isDead()) {
                system("cls");
                cout << "\n====================\n";
                cout << "������ �� Ǯ�� ���߽��ϴ�!\n";
                cout << "====================\n";
                cout << "������ �� Ǯ����, Ǭ ������ �� �������� ���Ͽ����ϴ�....\n\n";
                printLoseStory(player);
                earnedGPA += 0.0;
                player.addGPA(earnedGPA); // ���� ����
                fighting = false;
            }
        }
        else if (choice == '2')
        {
            if (player.getMonsterItemCount() <= 0) {
                cout << "�������� �����ϴ�.\n";
                Sleep(1000);
                system("cls");
                continue; // ���� ���·� ����
            }

            char subChoice;
            cout << "\n1. ����\n2. ���ư���\n����: ";
            cin >> subChoice;

            if (subChoice == '1') {
                player.useMonsterItem();
                Sleep(1000);
            }
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
    }
}

//ģ��(�߰�����) ��Ʋ�ý���
void BattleSystem::fightfriend(Player& player, Boss& boss)
{
    // ��ų ����
    Skill skill2("���", 50, 50);
    Skill skill3("����", 70, 30);

    system("cls");
    char choice;
    bool fighting = true;

    cout << player.getName() << "(��)�� " << boss.getName() << "���� �������� �޾Ҵ�!\n";
    Sleep(1000);
    system("cls");

    while (fighting)
    {
        // ��� ���� ���
        cout << boss.getName() << " : �� ������ Ǯ�����!\n";

        cout << "======== ���� ȭ�� ========\n";

        printStatus(player, boss);

        // �ൿ ����
        cout << "1. ���� Ǯ��\n";
        cout << "2. ������ ��� (�̱���)\n����: ";
        cin >> choice;

        if (choice == '1') {
            char atkChoice;
            cout << "\n� ������ ����ұ��?\n";
            cout << "1. ��Ÿ (10 ������, 100% ����)\n";
            cout << "2. " << skill2.getName() << " (" << skill2.getDamage() << " ������, " << skill2.getSuccessRate() << "% ����)\n";
            cout << "3. " << skill3.getName() << " (" << skill3.getDamage() << " ������, " << skill3.getSuccessRate() << "% ����)\n";
            cout << "����: ";
            cin >> atkChoice;

            int damage = 0, successRate = 0;
            switch (atkChoice) {
            case '1':
                damage = 10;
                successRate = 100;
                break;
            case '2':
                damage = skill2.getDamage();
                successRate = skill2.getSuccessRate();
                break;
            case '3':
                damage = skill3.getDamage();
                successRate = skill3.getSuccessRate();
                break;
            default:
                cout << "�߸��� �Է��Դϴ�.\n";
                Sleep(1000);
                continue;
            }

            // ���� ����
            system("cls");
            printStatus(player, boss);
            attack(player, boss, damage, successRate, player.getName(), boss.getName());

            if (boss.isDead()) {
                cout << "\n====================\n";
                cout << "�������� �� Ǯ�����ϴ�!\n";
                cout << "====================\n";
                if (player.hp >= 70) { // �¸� �� ���� (ü�� 70�̻�)

                }
                else if (player.hp > 0) { // �¸� �� ���� (ü�� 1~69)

                }
                fighting = false;
                continue;
            }

            attack(boss, player, boss.attack, 70, boss.getName(), player.getName());

            if (player.isDead()) {
                system("cls");
                cout << "\n====================\n";
                cout << "������ �� Ǯ�� ���߽��ϴ�! ���� ����!\n";
                cout << "====================\n";
                // ģ���� ���� �й� �� ���� X
                fighting = false;
            }
        }
        else if (choice == '2')
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

void BattleSystem::printStatus(const Player& player, const Boss& boss) // UI ����
{
    cout << "===========================\n";

    cout << left << setw(12) << "�÷��̾�" << " : "
        << right << setw(3) << player.hp << " / " << setw(3) << player.maxHP << " HP\n";

    cout << left << setw(12) << boss.name << " : "
        << right << setw(3) << boss.hp << " / " << setw(3) << boss.maxHP << " HP\n";

    cout << "===========================\n\n";
}
