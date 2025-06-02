#include "BattleSystem.h"
#include "Skill.h"
#include <iostream>
#include <cstdlib>
#define NOMINMAX // min, max ��ũ�� ���� ����
#include <windows.h>
#include <iomanip>
#include <limits>

using namespace std;

//������(����) ��Ʋ�ý���
void BattleSystem::fight(Player& player, Boss& boss) //char& grade ����
{
    system("cls");
    char choice;
    bool fighting = true;

    cout << player.getName() << "(��)�� " << boss.getName() << "���� �������� �޾Ҵ�!\n";
    Sleep(1000);
    system("cls");

    // ��ų ����
    Skill skill2("���", 50, 50);
    Skill skill3("����", 70, 30);

    while (fighting)
    {
        // ��� ���� ���
        cout << boss.getName() << " : �� ������ Ǯ�����!\n";

        cout << "======== ���� ȭ�� ========\n";

        printStatus(player, boss);

        // �ൿ ����
        cout << "1. ���� Ǯ��\n";
        cout << "2. ������ ���\n����: ";
        cin >> choice;
        cin.clear(); // �Է� ���� �ʱ�ȭ
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���� ����

        if (choice == '1') {
            char atkChoice;
            cout << "\n� ������ ����ұ��?\n";
            cout << "1. ��Ÿ (" << 10 * player.attack / 100 << " ������, 100% ����)\n";  // ���ݷ� �ݿ��� ������ ǥ��
            cout << "2. " << skill2.getName() << " (" << skill2.getDamage() * player.attack / 100 << " ������, " << skill2.getSuccessRate() << "% ����)\n";
            cout << "3. " << skill3.getName() << " (" << skill3.getDamage() * player.attack / 100 << " ������, " << skill3.getSuccessRate() << "% ����)\n";
            cout << "����: ";
            cin >> atkChoice;

            int baseDamage = 0, successRate = 0;
            switch (atkChoice) {
            case '1':
                baseDamage = 10;
                successRate = 100;
                break;
            case '2':
                baseDamage = skill2.getDamage();
                successRate = skill2.getSuccessRate();
                break;
            case '3':
                baseDamage = skill3.getDamage();
                successRate = skill3.getSuccessRate();
                break;
            default:
                cout << "�߸��� �Է��Դϴ�.\n";
                Sleep(1000);
				system("cls");
                continue;
            }

            // ���ݷ� �ݿ��� ���� ������ ���
            int finalDamage = baseDamage * player.attack / 100;

            // ���� ����
            system("cls");
            printStatus(player, boss);
            attack(player, boss, finalDamage, successRate, player.getName(), boss.getName());

            if (boss.isDead()) {
				system("cls");
                cout << "====================\n";
                cout << "�������� �� Ǯ�����ϴ�!\n";
                cout << "====================\n";
				if (player.hp >= 70) // �¸� �� ���� (ü�� 70�̻�)
                {
                    cout << "������ �� �¾� A������ �¾ҽ��ϴ�!\n\n";
                    player.addGold(1000); // ��� ����
					player.setGPA(4.0); // ���� ����
					player.addXP(800); // ����ġ ����
                }
				else if (player.hp >= 40) // �¸� �� ���� (ü�� 40 �̻� 70 �̸�)
                {
                    cout << "��� ������ Ʋ�� B������ �¾ҽ��ϴ�!\n\n";
                    player.addGold(800); // ��� ����
                    player.setGPA(3.0); // ���� ����
                    player.addXP(600); // ����ġ ����
                }
                else if (player.hp > 0) // �¸� �� ���� (ü�� 1 �̻� 40 �̸�)
                {
                    cout << "���� ������ Ʋ�� C������ �¾ҽ��ϴ�!\n\n";
                    player.addGold(500); // ��� ����
                    player.setGPA(2.0); // ���� ����
                    player.addXP(300); // ����ġ ����
                }
                fighting = false;
                continue;
            }

            // ���� ���� (���� �������� ���� �ݿ�)
            int bossDamage = boss.attack * 100 / player.defense; // ������ �������� ������ ����
            if (bossDamage < 5) bossDamage = 5; // �ּ� ������ ����
            attack(boss, player, bossDamage, 70, boss.getName(), player.getName());

            if (player.isDead()) {
                system("cls");
                cout << "====================\n";
                cout << "������ �� Ǯ�� ���߽��ϴ�! ���� ����!\n";
                cout << "====================\n";
				//�й� �� ���� X
				player.setGPA(0.0); // ���� ����
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
            cin.clear(); // �Է� ���� �ʱ�ȭ
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���� ����

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

    cout << player.getName() << "(��)�� " << boss.getName() << "���� ��������!\n";
    Sleep(1000);
    system("cls");

    while (1) {
		// ģ������ ���� ����
        cout << boss.getName() << " : �̰� ��� Ǯ��?\n";
		cout << "======== ���� ȭ�� ========\n";
		cout << "1. ģ���� ������ ���Ѵ�" << endl;
		cout << "2. �����Ѵ�" << endl;
		cout << "����: ";
		cin >> choice;
        cin.clear(); // �Է� ���� �ʱ�ȭ
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���� ����

		if (choice != '1' && choice != '2') {
			cout << "�߸��� �Է��Դϴ�. �ٽ� �������ּ���.\n";
			Sleep(1000);
			system("cls");
			continue;
		}
        else if (choice == '2') {
            cout << "ģ���� ������ �����ϰ� ����Ĩ�ϴ�.\n";
            break;
        }
		system("cls");
        while (fighting)
        {
            // ��� ���� ���
            cout << "======== ���� ȭ�� ========\n";

            printStatus(player, boss);

            // �ൿ ����
            cout << "1. ���� Ǯ���ֱ�\n";
            cout << "2. ������ ���\n����: ";
            cin >> choice;
            cin.clear(); // �Է� ���� �ʱ�ȭ
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���� ����

            if (choice == '1') {
                char atkChoice;
                cout << "\n� ������ ����ұ��?\n";
                cout << "1. ��Ÿ (" << 10 * player.attack / 100 << " ������, 100% ����)\n";  // ���ݷ� �ݿ��� ������ ǥ��
                cout << "2. " << skill2.getName() << " (" << skill2.getDamage() * player.attack / 100 << " ������, " << skill2.getSuccessRate() << "% ����)\n";
                cout << "3. " << skill3.getName() << " (" << skill3.getDamage() * player.attack / 100 << " ������, " << skill3.getSuccessRate() << "% ����)\n";
                cout << "����: ";
                cin >> atkChoice;

                int baseDamage = 0, successRate = 0;
                switch (atkChoice) {
                case '1':
                    baseDamage = 10;
                    successRate = 100;
                    break;
                case '2':
                    baseDamage = skill2.getDamage();
                    successRate = skill2.getSuccessRate();
                    break;
                case '3':
                    baseDamage = skill3.getDamage();
                    successRate = skill3.getSuccessRate();
                    break;
                default:
                    cout << "�߸��� �Է��Դϴ�.\n";
                    Sleep(1000);
                    system("cls");
                    continue;
                }

                // ���ݷ� �ݿ��� ���� ������ ���
                int finalDamage = baseDamage * player.attack / 100;

                // ���� ����
                system("cls");
                printStatus(player, boss);
                attack(player, boss, finalDamage, successRate, player.getName(), boss.getName());

                if (boss.isDead()) {
					system("cls");
                    cout << "====================\n";
                    cout << "������ Ǯ���ְ� ������ �����߽��ϴ�!\n";
                    cout << "====================\n";
					if (player.hp >= 70) // �¸� �� ���� (ü�� 70�̻�)
                    {
                        player.addGold(400); // ��� ����
                        player.addXP(300); // ����ġ ����
                    }
					else if (player.hp > 0) // �¸� �� ���� (ü�� 1~69)
                    {
                        player.addGold(300); // ��� ����
                        player.addXP(200); // ����ġ ����
                    }
                    fighting = false;
                    continue;
                }

                // ���� ���� (���� �������� ���� �ݿ�)
                int bossDamage = boss.attack * 100 / player.defense; // ������ �������� ������ ����
                if (bossDamage < 5) bossDamage = 5; // �ּ� ������ ����
                attack(boss, player, bossDamage, 70, boss.getName(), player.getName());

                if (player.isDead()) {
                    system("cls");
                    cout << "====================\n";
                    cout << "������ �� Ǯ�� ���߽��ϴ�! ���� ����!\n";
                    cout << "====================\n";
                    // ģ���� ���� �й� �� ���� X
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
                cin.clear(); // �Է� ���� �ʱ�ȭ
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���� ����

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
		break; // ģ������ ���� ����
    }
}

void BattleSystem::attack(Character& attacker, Character& defender, int damage, int successRate, const string& attackerName, const string& defenderName) {
    cout << attackerName << "�� ����!\n";
    if (isAttackSuccessful(successRate)) {
        // ���� ��� (����ڰ� �÷��̾��� ��쿡�� ���� ����)
        int finalDamage = damage;
        if (typeid(defender) == typeid(Player)) {
            finalDamage = damage * 100 / defender.defense;
            if (finalDamage < 1) finalDamage = 1; // �ּ� 1 ������
        }

        defender.takeDamage(finalDamage);
        cout << "���� ����! " << defenderName << "���� " << finalDamage << " ����!";

        // �߰� ���� ǥ�� (���ݷ�/���� �ݿ� ����)
        if (finalDamage != damage) {
            cout << " (�⺻ " << damage << "���� ���� " << defender.defense << "% �ݿ�)";
        }
        cout << "\n";
    }
    else {
        cout << "���� ����!\n";
    }
    Sleep(1000);
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
