#include "BattleSystem.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>
//��Ʋ�ý���
void BattleSystem::fight(Player& player, Boss& boss) {
    system("cls");
    char choice;
    bool fighting = true;

    while (fighting) {
        // ��� ���� ���
        std::cout << "���� : �� ������ Ǯ�����!\n";
        printStatus(player, boss);

        // �ൿ ����
        std::cout << "1. ���� Ǯ��\n";
        std::cout << "2. ������ ��� (�̱���)\n����: ";
        std::cin >> choice;

        if (choice == '1') {
            char atkChoice;
            std::cout << "\n� ������ ����ұ��?\n";
            std::cout << "1. Ǯ�� (30 ������, 70% ����)\n";
            std::cout << "2. ��� (50 ������, 50% ����)\n";
            std::cout << "3. �����ϱ� (70 ������, 30% ����)\n";
            std::cout << "����: ";
            std::cin >> atkChoice;

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
                std::cout << "====================\n";
                std::cout << "�������� �� Ǯ�����ϴ�!\n";
                std::cout << "====================\n";
                fighting = false;
                continue;
            }

            attack(boss, player, 30, 70, "����", "���ΰ�");

            if (player.isDead()) {
                system("cls");
                std::cout << "====================\n";
                std::cout << "������ �� Ǯ�� ���߽��ϴ�! ���� ����!\n";
                std::cout << "====================\n";
                fighting = false;
            }
        }
        else if(choice == '2'){
            std::cout << "������ ����� ���� �������� �ʾҽ��ϴ�.\n";
            Sleep(1500); //1.5�� ����
        }

        // �ൿ �� ȭ�� ���� (HP�� ����)
        if (fighting)
        {
            system("cls");
        }
    }
}

void BattleSystem::attack(Character& attacker, Character& defender, int damage, int successRate, const std::string& attackerName, const std::string& defenderName) {
    std::cout << attackerName << "�� ����!\n";
    if (isAttackSuccessful(successRate)) {
        defender.takeDamage(damage);
        std::cout << "���� ����! " << defenderName << "���� " << damage << " ����!\n";
    }
    else {
        std::cout << "���� ����!\n";
    }
    Sleep(1500); //1.5�� ����
}

bool BattleSystem::isAttackSuccessful(int successRate) {
    return rand() % 100 < successRate;
}

void BattleSystem::printStatus(const Player& player, const Boss& boss) {
    std::cout << "====================\n";
    std::cout << "�÷��̾� : " << player.hp << " / " << player.maxHP << " HP\n";
    std::cout << "������ : " << boss.hp << " / " << boss.maxHP << " HP\n";
    std::cout << "====================\n\n";
}
