#include "BattleSystem.h"
#include "Skill.h"
#include "StorySystem.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <iomanip>

using namespace std;

//교수님(보스) 배틀시스템
void BattleSystem::fight(Player& player, Boss& boss, double& gpa) //gpa = 학점 시스템
{
    double earnedGPA = 0.0;
    system("cls");
    char choice;
    bool fighting = true;

    cout << player.getName() << "(이)가 " << boss.getName() << "에게 시험지를 받았다!\n";
    Sleep(1000);
    system("cls");

    // 스킬 정의
    Skill skill2("찍기", 50, 50);
    Skill skill3("컨닝", 70, 100);

    while (fighting)
    {
        // 상단 상태 출력
        cout << boss.getName() << " : 이 문제도 풀어보시지!\n";

        cout << "======== 전투 화면 ========\n";

        printStatus(player, boss);

        // 행동 선택
        cout << "1. 문제 풀기\n";
        cout << "2. 아이템 사용\n";
        cout << "선택: ";
        cin >> choice;

        if (choice == '1') {
            char atkChoice;
            cout << "\n어떤 공격을 사용할까요?\n";
            cout << "1. 평타 (10 데미지, 100% 성공)\n";
            cout << "2. " << skill2.getName() << " (" << skill2.getDamage() << " 데미지, " << skill2.getSuccessRate() << "% 성공)\n";
            cout << "3. " << skill3.getName() << " (" << skill3.getDamage() << " 데미지, " << skill3.getSuccessRate() << "% 성공)\n";
            cout << "선택: ";
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
                cout << "잘못된 입력입니다.\n";
                Sleep(1000);
                continue;
            }

            // 전투 진행
            system("cls");
            printStatus(player, boss);
            attack(player, boss, damage, successRate, player.getName(), boss.getName());

            if (boss.isDead()) {
                cout << "\n====================\n";
                cout << "시험지를 다 풀었습니다!\n";
                cout << "====================\n";
                if (player.hp >= 70) // 70 이상
                {
                    cout << "문제를 다 맞아 A학점을 맞았습니다!\n\n";
                    earnedGPA += 4.0;
                    Sleep(1500);
                }
                else if (player.hp >= 40)  // 40 이상 70 미만
                {
                    cout << "몇몇 문제를 틀려 B학점을 맞았습니다!\n\n";
                    earnedGPA += 3.0;
                    Sleep(1500);
                }
                else if (player.hp > 0)    // 1 이상 39 이하
                {
                    cout << "많은 문제를 틀려 C학점을 맞았습니다!\n\n";
                    earnedGPA += 2.0;
                    Sleep(1500);
                }
                printWinStory(player);
                player.addGPA(earnedGPA); // 누적 저장
                fighting = false;
                continue;
            }

            attack(boss, player, boss.attack, 70, boss.getName(), player.getName());

            if (player.isDead()) {
                system("cls");
                cout << "\n====================\n";
                cout << "문제를 다 풀지 못했습니다!\n";
                cout << "====================\n";
                cout << "문제를 다 풀지도, 푼 문제를 다 맞추지도 못하였습니다....\n\n";
                printLoseStory(player);
                earnedGPA += 0.0;
                player.addGPA(earnedGPA); // 누적 저장
                fighting = false;
            }
        }
        else if (choice == '2')
        {
            if (player.getMonsterItemCount() <= 0) {
                cout << "아이템이 없습니다.\n";
                Sleep(1000);
                system("cls");
                continue; // 이전 상태로 복귀
            }

            char subChoice;
            cout << "\n1. 몬스터\n2. 돌아가기\n선택: ";
            cin >> subChoice;

            if (subChoice == '1') {
                player.useMonsterItem();
                Sleep(1000);
            }
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
    }
}

//친구(중간보스) 배틀시스템
void BattleSystem::fightfriend(Player& player, Boss& boss)
{
    // 스킬 정의
    Skill skill2("찍기", 50, 50);
    Skill skill3("컨닝", 70, 30);

    system("cls");
    char choice;
    bool fighting = true;

    cout << player.getName() << "(이)가 " << boss.getName() << "에게 시험지를 받았다!\n";
    Sleep(1000);
    system("cls");

    while (fighting)
    {
        // 상단 상태 출력
        cout << boss.getName() << " : 이 문제도 풀어보시지!\n";

        cout << "======== 전투 화면 ========\n";

        printStatus(player, boss);

        // 행동 선택
        cout << "1. 문제 풀기\n";
        cout << "2. 아이템 사용 (미구현)\n선택: ";
        cin >> choice;

        if (choice == '1') {
            char atkChoice;
            cout << "\n어떤 공격을 사용할까요?\n";
            cout << "1. 평타 (10 데미지, 100% 성공)\n";
            cout << "2. " << skill2.getName() << " (" << skill2.getDamage() << " 데미지, " << skill2.getSuccessRate() << "% 성공)\n";
            cout << "3. " << skill3.getName() << " (" << skill3.getDamage() << " 데미지, " << skill3.getSuccessRate() << "% 성공)\n";
            cout << "선택: ";
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
                cout << "잘못된 입력입니다.\n";
                Sleep(1000);
                continue;
            }

            // 전투 진행
            system("cls");
            printStatus(player, boss);
            attack(player, boss, damage, successRate, player.getName(), boss.getName());

            if (boss.isDead()) {
                cout << "\n====================\n";
                cout << "시험지를 다 풀었습니다!\n";
                cout << "====================\n";
                if (player.hp >= 70) { // 승리 시 보상 (체력 70이상)

                }
                else if (player.hp > 0) { // 승리 시 보상 (체력 1~69)

                }
                fighting = false;
                continue;
            }

            attack(boss, player, boss.attack, 70, boss.getName(), player.getName());

            if (player.isDead()) {
                system("cls");
                cout << "\n====================\n";
                cout << "문제를 다 풀지 못했습니다! 게임 오버!\n";
                cout << "====================\n";
                // 친구와 전투 패배 시 보상 X
                fighting = false;
            }
        }
        else if (choice == '2')
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

void BattleSystem::printStatus(const Player& player, const Boss& boss) // UI 수정
{
    cout << "===========================\n";

    cout << left << setw(12) << "플레이어" << " : "
        << right << setw(3) << player.hp << " / " << setw(3) << player.maxHP << " HP\n";

    cout << left << setw(12) << boss.name << " : "
        << right << setw(3) << boss.hp << " / " << setw(3) << boss.maxHP << " HP\n";

    cout << "===========================\n\n";
}
