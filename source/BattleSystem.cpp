#include "BattleSystem.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>
//배틀시스템
void BattleSystem::fight(Player& player, Boss& boss) {
    system("cls");
    char choice;
    bool fighting = true;

    while (fighting) {
        // 상단 상태 출력
        std::cout << "교수 : 이 문제도 풀어보시지!\n";
        printStatus(player, boss);

        // 행동 선택
        std::cout << "1. 문제 풀기\n";
        std::cout << "2. 아이템 사용 (미구현)\n선택: ";
        std::cin >> choice;

        if (choice == '1') {
            char atkChoice;
            std::cout << "\n어떤 공격을 사용할까요?\n";
            std::cout << "1. 풀기 (30 데미지, 70% 성공)\n";
            std::cout << "2. 찍기 (50 데미지, 50% 성공)\n";
            std::cout << "3. 컨닝하기 (70 데미지, 30% 성공)\n";
            std::cout << "선택: ";
            std::cin >> atkChoice;

            int damage = 0, successRate = 0;
            switch (atkChoice) {
            case '1': damage = 30; successRate = 70; break;
            case '2': damage = 50; successRate = 50; break;
            case '3': damage = 70; successRate = 30; break;
            default: continue;
            }
            // 전투 진행
            system("cls");
            printStatus(player, boss);
            attack(player, boss, damage, successRate, "주인공", "교수님");

            if (boss.isDead()) {
                std::cout << "====================\n";
                std::cout << "시험지를 다 풀었습니다!\n";
                std::cout << "====================\n";
                fighting = false;
                continue;
            }

            attack(boss, player, 30, 70, "보스", "주인공");

            if (player.isDead()) {
                system("cls");
                std::cout << "====================\n";
                std::cout << "문제를 다 풀지 못했습니다! 게임 오버!\n";
                std::cout << "====================\n";
                fighting = false;
            }
        }
        else if(choice == '2'){
            std::cout << "아이템 기능은 아직 구현되지 않았습니다.\n";
            Sleep(1500); //1.5초 정지
        }

        // 행동 후 화면 리셋 (HP만 유지)
        if (fighting)
        {
            system("cls");
        }
    }
}

void BattleSystem::attack(Character& attacker, Character& defender, int damage, int successRate, const std::string& attackerName, const std::string& defenderName) {
    std::cout << attackerName << "의 공격!\n";
    if (isAttackSuccessful(successRate)) {
        defender.takeDamage(damage);
        std::cout << "공격 성공! " << defenderName << "에게 " << damage << " 피해!\n";
    }
    else {
        std::cout << "공격 실패!\n";
    }
    Sleep(1500); //1.5초 정지
}

bool BattleSystem::isAttackSuccessful(int successRate) {
    return rand() % 100 < successRate;
}

void BattleSystem::printStatus(const Player& player, const Boss& boss) {
    std::cout << "====================\n";
    std::cout << "플레이어 : " << player.hp << " / " << player.maxHP << " HP\n";
    std::cout << "교수님 : " << boss.hp << " / " << boss.maxHP << " HP\n";
    std::cout << "====================\n\n";
}
