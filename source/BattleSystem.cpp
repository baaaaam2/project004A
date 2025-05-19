#include "BattleSystem.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>

using namespace std;

//배틀시스템
void BattleSystem::fight(Player& player, Boss& boss) {
    system("cls");
    char choice;
    bool fighting = true;

    while (fighting) {
        // 상단 상태 출력
        cout << "교수 : 이 문제도 풀어보시지!\n";
        printStatus(player, boss);

        // 행동 선택
        cout << "1. 문제 풀기\n";
        cout << "2. 아이템 사용 (미구현)\n선택: ";
        cin >> choice;

        if (choice == '1') {
            char atkChoice;
            cout << "\n어떤 공격을 사용할까요?\n";
            cout << "1. 풀기 (30 데미지, 70% 성공)\n";
            cout << "2. 찍기 (50 데미지, 50% 성공)\n";
            cout << "3. 컨닝하기 (70 데미지, 30% 성공)\n";
            cout << "선택: ";
            cin >> atkChoice;

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
                cout << "====================\n";
                cout << "시험지를 다 풀었습니다!\n";
                cout << "====================\n";
                fighting = false;
                continue;
            }

            attack(boss, player, 30, 70, "보스", "주인공");

            if (player.isDead()) {
                system("cls");
                cout << "====================\n";
                cout << "문제를 다 풀지 못했습니다! 게임 오버!\n";
                cout << "====================\n";
                fighting = false;
            }
        }
        else if(choice == '2'){
            cout << "아이템 기능은 아직 구현되지 않았습니다.\n";
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
        cout << "공격 성공! " << defenderName << "에게 " << damage << " 피해!\n";
    }
    else {
        cout << "공격 실패!\n";
    }
    Sleep(1500); //1.5초 정지
}

bool BattleSystem::isAttackSuccessful(int successRate) {
    return rand() % 100 < successRate;
}

void BattleSystem::printStatus(const Player& player, const Boss& boss) {
    cout << "====================\n";
    cout << "플레이어 : " << player.hp << " / " << player.maxHP << " HP\n";
    cout << "교수님 : " << boss.hp << " / " << boss.maxHP << " HP\n";
    cout << "====================\n\n";
}
