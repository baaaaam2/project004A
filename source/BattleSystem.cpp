#include "BattleSystem.h"
#include "Skill.h"
#include <iostream>
#include <cstdlib>
#define NOMINMAX // min, max 매크로 정의 방지
#include <windows.h>
#include <iomanip>
#include <limits>

using namespace std;

//교수님(보스) 배틀시스템
void BattleSystem::fight(Player& player, Boss& boss) //char& grade 삭제
{
    system("cls");
    char choice;
    bool fighting = true;

    cout << player.getName() << "(이)가 " << boss.getName() << "에게 시험지를 받았다!\n";
    Sleep(1000);
    system("cls");

    // 스킬 정의
    Skill skill2("찍기", 50, 50);
    Skill skill3("컨닝", 70, 30);

    while (fighting)
    {
        // 상단 상태 출력
        cout << boss.getName() << " : 이 문제도 풀어보시지!\n";

        cout << "======== 전투 화면 ========\n";

        printStatus(player, boss);

        // 행동 선택
        cout << "1. 문제 풀기\n";
        cout << "2. 아이템 사용\n선택: ";
        cin >> choice;
        cin.clear(); // 입력 버퍼 초기화
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 버퍼 비우기

        if (choice == '1') {
            char atkChoice;
            cout << "\n어떤 공격을 사용할까요?\n";
            cout << "1. 평타 (" << 10 * player.attack / 100 << " 데미지, 100% 성공)\n";  // 공격력 반영된 데미지 표시
            cout << "2. " << skill2.getName() << " (" << skill2.getDamage() * player.attack / 100 << " 데미지, " << skill2.getSuccessRate() << "% 성공)\n";
            cout << "3. " << skill3.getName() << " (" << skill3.getDamage() * player.attack / 100 << " 데미지, " << skill3.getSuccessRate() << "% 성공)\n";
            cout << "선택: ";
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
                cout << "잘못된 입력입니다.\n";
                Sleep(1000);
				system("cls");
                continue;
            }

            // 공격력 반영된 최종 데미지 계산
            int finalDamage = baseDamage * player.attack / 100;

            // 전투 진행
            system("cls");
            printStatus(player, boss);
            attack(player, boss, finalDamage, successRate, player.getName(), boss.getName());

            if (boss.isDead()) {
				system("cls");
                cout << "====================\n";
                cout << "시험지를 다 풀었습니다!\n";
                cout << "====================\n";
				if (player.hp >= 70) // 승리 시 보상 (체력 70이상)
                {
                    cout << "문제를 다 맞아 A학점을 맞았습니다!\n\n";
                    player.addGold(1000); // 골드 보상
					player.setGPA(4.0); // 학점 보상
					player.addXP(800); // 경험치 보상
                }
				else if (player.hp >= 40) // 승리 시 보상 (체력 40 이상 70 미만)
                {
                    cout << "몇몇 문제를 틀려 B학점을 맞았습니다!\n\n";
                    player.addGold(800); // 골드 보상
                    player.setGPA(3.0); // 학점 보상
                    player.addXP(600); // 경험치 보상
                }
                else if (player.hp > 0) // 승리 시 보상 (체력 1 이상 40 미만)
                {
                    cout << "많은 문제를 틀려 C학점을 맞았습니다!\n\n";
                    player.addGold(500); // 골드 보상
                    player.setGPA(2.0); // 학점 보상
                    player.addXP(300); // 경험치 보상
                }
                fighting = false;
                continue;
            }

            // 보스 공격 (보스 데미지에 방어력 반영)
            int bossDamage = boss.attack * 100 / player.defense; // 방어력이 높을수록 데미지 감소
            if (bossDamage < 5) bossDamage = 5; // 최소 데미지 보장
            attack(boss, player, bossDamage, 70, boss.getName(), player.getName());

            if (player.isDead()) {
                system("cls");
                cout << "====================\n";
                cout << "문제를 다 풀지 못했습니다! 게임 오버!\n";
                cout << "====================\n";
				//패배 시 보상 X
				player.setGPA(0.0); // 학점 보상
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
            cin.clear(); // 입력 버퍼 초기화
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 버퍼 비우기

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

    cout << player.getName() << "(이)가 " << boss.getName() << "에게 붙잡혔다!\n";
    Sleep(1000);
    system("cls");

    while (1) {
		// 친구와의 전투 시작
        cout << boss.getName() << " : 이거 어떻게 풀어?\n";
		cout << "======== 선택 화면 ========\n";
		cout << "1. 친구의 물음에 응한다" << endl;
		cout << "2. 무시한다" << endl;
		cout << "선택: ";
		cin >> choice;
        cin.clear(); // 입력 버퍼 초기화
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 버퍼 비우기

		if (choice != '1' && choice != '2') {
			cout << "잘못된 입력입니다. 다시 선택해주세요.\n";
			Sleep(1000);
			system("cls");
			continue;
		}
        else if (choice == '2') {
            cout << "친구의 물음을 무시하고 지나칩니다.\n";
            break;
        }
		system("cls");
        while (fighting)
        {
            // 상단 상태 출력
            cout << "======== 전투 화면 ========\n";

            printStatus(player, boss);

            // 행동 선택
            cout << "1. 문제 풀어주기\n";
            cout << "2. 아이템 사용\n선택: ";
            cin >> choice;
            cin.clear(); // 입력 버퍼 초기화
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 버퍼 비우기

            if (choice == '1') {
                char atkChoice;
                cout << "\n어떤 공격을 사용할까요?\n";
                cout << "1. 평타 (" << 10 * player.attack / 100 << " 데미지, 100% 성공)\n";  // 공격력 반영된 데미지 표시
                cout << "2. " << skill2.getName() << " (" << skill2.getDamage() * player.attack / 100 << " 데미지, " << skill2.getSuccessRate() << "% 성공)\n";
                cout << "3. " << skill3.getName() << " (" << skill3.getDamage() * player.attack / 100 << " 데미지, " << skill3.getSuccessRate() << "% 성공)\n";
                cout << "선택: ";
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
                    cout << "잘못된 입력입니다.\n";
                    Sleep(1000);
                    system("cls");
                    continue;
                }

                // 공격력 반영된 최종 데미지 계산
                int finalDamage = baseDamage * player.attack / 100;

                // 전투 진행
                system("cls");
                printStatus(player, boss);
                attack(player, boss, finalDamage, successRate, player.getName(), boss.getName());

                if (boss.isDead()) {
					system("cls");
                    cout << "====================\n";
                    cout << "문제를 풀어주고 지식을 습득했습니다!\n";
                    cout << "====================\n";
					if (player.hp >= 70) // 승리 시 보상 (체력 70이상)
                    {
                        player.addGold(400); // 골드 보상
                        player.addXP(300); // 경험치 보상
                    }
					else if (player.hp > 0) // 승리 시 보상 (체력 1~69)
                    {
                        player.addGold(300); // 골드 보상
                        player.addXP(200); // 경험치 보상
                    }
                    fighting = false;
                    continue;
                }

                // 보스 공격 (보스 데미지에 방어력 반영)
                int bossDamage = boss.attack * 100 / player.defense; // 방어력이 높을수록 데미지 감소
                if (bossDamage < 5) bossDamage = 5; // 최소 데미지 보장
                attack(boss, player, bossDamage, 70, boss.getName(), player.getName());

                if (player.isDead()) {
                    system("cls");
                    cout << "====================\n";
                    cout << "문제를 다 풀지 못했습니다! 게임 오버!\n";
                    cout << "====================\n";
                    // 친구와 전투 패배 시 보상 X
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
                cin.clear(); // 입력 버퍼 초기화
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 버퍼 비우기

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
		break; // 친구와의 전투 종료
    }
}

void BattleSystem::attack(Character& attacker, Character& defender, int damage, int successRate, const string& attackerName, const string& defenderName) {
    cout << attackerName << "의 공격!\n";
    if (isAttackSuccessful(successRate)) {
        // 방어력 계산 (방어자가 플레이어인 경우에만 방어력 적용)
        int finalDamage = damage;
        if (typeid(defender) == typeid(Player)) {
            finalDamage = damage * 100 / defender.defense;
            if (finalDamage < 1) finalDamage = 1; // 최소 1 데미지
        }

        defender.takeDamage(finalDamage);
        cout << "공격 성공! " << defenderName << "에게 " << finalDamage << " 피해!";

        // 추가 정보 표시 (공격력/방어력 반영 정보)
        if (finalDamage != damage) {
            cout << " (기본 " << damage << "에서 방어력 " << defender.defense << "% 반영)";
        }
        cout << "\n";
    }
    else {
        cout << "공격 실패!\n";
    }
    Sleep(1000);
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
