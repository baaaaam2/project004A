#include "game.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

//캐릭터
Character::Character(int maxHP, int attack, int defense)
    : maxHP(maxHP), hp(maxHP), attack(attack), defense(defense) {
}

//데미지를 받는 함수
void Character::takeDamage(int amount)
{
    hp -= amount;
    if (hp < 0) hp = 0;
}

//죽음 감지
bool Character::isDead() const
{
    return hp <= 0;
}

//플레이어
Player::Player(string name)
    : Character(100, 30, 10), name(move(name)) {
} //체력 100, 공격력 30, 방어력 10

//보스
Boss::Boss()
    : Character(100, 30, 10) {
} //체력 100, 공격력 30, 방어력 10

//맵
Map::Map() {
    initialize();
}

void Map::initialize() 
{   
    //맵을 ' '으로 초기화
    for (int y = 0; y < MAP_HEIGHT; ++y)
        for (int x = 0; x < MAP_WIDTH; ++x)
            tiles[y][x] = ' '; 
    //상단, 하단 경계
    for (int x = 0; x < MAP_WIDTH; ++x)
        tiles[0][x] = tiles[MAP_HEIGHT - 1][x] = (x == 0 || x == MAP_WIDTH - 1) ? '|' : '-';
    //좌측, 우측 경계
    for (int y = 1; y < MAP_HEIGHT - 1; ++y) {
        tiles[y][0] = '|';
        tiles[y][MAP_WIDTH - 1] = '|';
    }
    //보스 위치
    tiles[BOSS_Y][BOSS_X] = 'P'; 
}

void Map::print(const Player& player, int playerX, int playerY) //맵 출력
{
    system("cls");
    //주인공 이름, 이동방법 출력
    cout << "주인공 : " << player.name << "\n";
    cout << "이동 : W(위), A(왼쪽), S(아래), D(오른쪽), 종료: Q\n";
    //맵 및 현제 상태 출력
    for (int y = 0; y < MAP_HEIGHT; ++y) 
    {
        for (int x = 0; x < MAP_WIDTH; ++x) 
        {
            if (x == playerX && y == playerY) cout << '@'; //플레이어 위치, 출력
            else if (y == BOSS_LABEL_Y && x >= BOSS_X - 4 && x < BOSS_X + 4) //보스 위치, 출력
                cout << "<<boss>>"[x - (BOSS_X - 4)]; //보스 라벨 위치, 출력
            else cout << tiles[y][x]; //맵의 기본 타일 출력 : ' ', '-', '|'
        }
        cout << "   "; //공백 3칸으로 맵과 분리
        if (y == 0)  cout << "==========================";
        else if (y == 1) cout << "체력 : " << player.hp << " / " << player.maxHP << " HP";
        else if (y == 2) cout << "방어력 : " << player.defense;
        else if (y == 3) cout << "공부력 : " << player.attack;
        else if (y == 4) cout << "==========================";
        else if (y == 5) cout << "인벤토리";
        else if (y == 6) cout << "전공책";
        else if (y == 7) cout << "계산기";
        else if (y == 8) cout << "휴대폰";
        else if (y == 9) cout << "==========================";
        cout << endl;
    }
}

char Map::getTile(int x, int y) const {
    return tiles[y][x];
}

void Map::setTile(int x, int y, char symbol) {
    tiles[y][x] = symbol;
}

//배틀시스템
void BattleSystem::fight(Player& player, Boss& boss) {
    system("cls");
    bool fighting = true;
    char choice;

    while (fighting) {
        // 상단 상태 출력
        cout << "교수 : 이 문제도 풀어보시지!\n";
        printStatus(player, boss);

        // 행동 선택
        cout << "교수가 시험지를 건냈다 : \n";
        cout << "1. 문제 풀기\n";
        cout << "2. 아이템 사용 (현재는 아이템 기능이 없습니다)\n";
        cout << "선택: ";
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
                system("cls");
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
        else if (choice == '2') {
            cout << "아이템 기능은 아직 구현되지 않았습니다.\n";
            Sleep(1500); //1.5초 정지
        }

        // 행동 후 화면 리셋 (HP만 유지)
        if (fighting) {
            system("cls");
        }
    }
}

void BattleSystem::printStatus(const Player& player, const Boss& boss) {
    cout << "====================\n";
    cout << "플레이어 : " << player.hp << " / " << player.maxHP << " HP\n";
    cout << "교수님 : " << boss.hp << " / " << boss.maxHP << " HP\n";
    cout << "====================\n\n";
}

void BattleSystem::attack(Character& attacker, Character& defender, int damage, int successRate, const string& attackerName, const string& defenderName) {
    cout << attackerName << "의 공격!\n";
    if (isAttackSuccessful(successRate)) {
        defender.takeDamage(damage);
        cout << "공격 성공! " << defenderName << "에게 " << damage << " 피해!\n";
    }
    else {
        cout << "공격 실패! 공격이 빗나갔습니다.\n";
    }
    cout << endl;
    Sleep(1500); //1.5초 정지
}

bool BattleSystem::isAttackSuccessful(int successRate) {
    return rand() % 100 < successRate;
}

//컨트롤러
Controller::Controller(Player& p, Boss& b, Map& m)
    : player(p), boss(b), map(m) {
}

void Controller::startGame() {
    srand((unsigned)time(0));
    cout << "주인공의 이름을 입력하세요: ";
    getline(cin, player.name); //플레이어 이름 설정

    map.initialize();
    char input;
    bool gameRunning = true;

    while (gameRunning) {
        map.print(player, playerX, playerY);
        input = _getch();

        if (input == 'q' || input == 'Q') //q 입력시 종료
        {
            gameRunning = false;
        }
        else if (movePlayer(input)) {
            if (map.getTile(playerX, playerY) == 'P') {
                system("cls");
                BattleSystem bs;
                bs.fight(player, boss);
                gameRunning = false;
            }
        }
    }

    cout << "게임 종료!" << endl;
}

bool Controller::movePlayer(char input) {
    int newX = playerX, newY = playerY;
    switch (input) {
    case 'w': case 'W': newY--; break; //w,W 입력시 Y-1 (위로)
    case 's': case 'S': newY++; break; //s,S 입력시 Y+1 (밑으로)
    case 'a': case 'A': newX--; break; //a,A 입력시 X-1 (왼쪽으로)
    case 'd': case 'D': newX++; break; //d,D 입력시 X+1 (오른쪽으로)
    default: return false;
    }

    char tile = map.getTile(newX, newY);
    if (tile != '|' && tile != '-') {
        playerX = newX;
        playerY = newY;
        return true;
    }
    return false;
}