#include "BattleSystem.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>
#define MAX_TURNS 10

using namespace std;

//교수님(보스) 배틀시스템
void BattleSystem::fight(Player& player, Boss& boss, char& grade) //char& grade 추가
{
    system("cls");
    char choice;
    int turn = 1;
    bool fighting = true;

    cout << player.getName() << "(이)가 " << boss.getName() << "에게 시험지를 받았다!\n";
    Sleep(1000);
    system("cls");

    while (player.isAlive() && boss.isAlive() && turn <= MAX_TURNS) 
    {
        // 상단 상태 출력
        cout << boss.getName() << " : 이 문제도 풀어보시지!\n";

        cout << "======= 전투 화면 ======\n";
        cout << "[남은 시험 시간 " << turn << " / " << MAX_TURNS << "]\n";

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
                cout << "\n====================\n";
                cout << "시험지를 다 풀었습니다!\n";
                cout << "====================\n";
                if (player.hp >= 70) grade = 'A'; // 체력 70 이상: A학점
                else if (player.hp > 0) grade = 'B'; // 체력 1~69: B학점
                fighting = false;
                continue;
            }

            attack(boss, player, 30, 70, "보스", "주인공");

            if (player.isDead()) {
                system("cls");
                cout << "\n====================\n";
                cout << "문제를 다 풀지 못했습니다! 게임 오버!\n";
                cout << "====================\n";
                grade = 'C'; // 패배: C학점
                fighting = false;
            }
        }
        else if(choice == '2')
        {
            cout << "아이템 기능은 아직 구현되지 않았습니다.\n";
            Sleep(1500); //1.5초 정지
        }
        else if (choice != 2 || choice != 1)
        {
            cout << "알맞은 옵션을 선택해주세요.\n";
            Sleep(1500);
        }

        // 행동 후 화면 리셋 (HP만 유지)
        if (fighting)
        {
            system("cls");
        }
        turn++;
    }
}

//친구(중간보스) 배틀시스템
void BattleSystem::fightfriend(Player& player, Boss& boss)
{
    system("cls");
    char choice;
    bool fighting = true;

    std::cout << player.getName() << "(이)가 " << boss.getName() << "에게 질문을 받았다!\n";
    Sleep(1000);

    while (fighting) {
        std::cout << boss.getName() << " : 이거 어떻게 풀어?\n" << std::endl;
        printStatus(player, boss);
        std::cout << "1. 문제 풀기\n";
        std::cout << "2. 아이템 사용 (미구현)\n선택: ";
        std::cin >> choice;
        if (choice == '1') {
            char atkChoice;
            std::cout << "1. 풀기 (30, 70%)\n2. 찍기 (50, 50%)\n3. 컨닝 (70, 30%)\n선택: ";
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
            attack(player, boss, damage, successRate, "주인공", "친구");
            if (boss.isDead()) {
                std::cout << "시험지를 다 풀었습니다!\n";
                fighting = false;
                continue;
            }
            attack(boss, player, 30, 70, "보스", "주인공");
            if (player.isDead()) {
                std::cout << "문제를 다 풀지 못했습니다! 게임 오버!\n";
                fighting = false;
            }
        }
        else {
            std::cout << "아이템 기능은 아직 구현되지 않았습니다.\n";
            Sleep(1500);
        }
        if (fighting) system("cls");
    }
}

void BattleSystem::attack(Character& attacker, Character& defender, int damage, int successRate, const string& attackerName, const string& defenderName) {
    cout << attackerName << "의 공격!\n";
    if (isAttackSuccessful(successRate)) {
        defender.takeDamage(damage);
        cout << "공격 성공! " << defenderName << "에게 " << damage << " 피해!\n";
    }
    else {
        cout << "공격 실패!\n";
    }
    Sleep(1000); //1초 정지
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
