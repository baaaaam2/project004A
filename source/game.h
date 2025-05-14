#ifndef GAME_H
#define GAME_H

#include <string>

using namespace std;

const int MAP_WIDTH = 30; //맵 X축 크기
const int MAP_HEIGHT = 20; //맵 Y축 크리
const int BOSS_X = MAP_WIDTH - 5; //보스 X축 위치
const int BOSS_Y = MAP_HEIGHT - 2; //보스 Y축 위치
const int BOSS_LABEL_Y = MAP_HEIGHT - 3; //보스 라벨 위치

//캐릭터 클래스
class Character {
public:
    Character(int maxHP, int attack, int defense);
    virtual ~Character() = default;

    virtual void takeDamage(int amount);
    bool isDead() const;

    int maxHP; //최대체력
    int hp; //현제체력
    int attack; //공격력
    int defense; //방어력
};

//플레이어 클래스 <= 캐릭터 상속
class Player : public Character {
public:
    Player(string name); //플레이어 이름 설정
    string name;
};

//보스 클래스 <= 캐릭터 상속
class Boss : public Character {
public:
    Boss(); 
};

//맵 클래스
class Map {
public:
    Map();
    void initialize();
    void print(const Player& player, int playerX, int playerY);
    char getTile(int x, int y) const;
    void setTile(int x, int y, char symbol);

private:
    char tiles[MAP_HEIGHT][MAP_WIDTH];
};

//배틀시스템 클래스
class BattleSystem {
public:
    void fight(Player& player, Boss& boss);

private:
    void attack(Character& attacker, Character& defender, int damage, int successRate, const std::string& attackerName, const std::string& defenderName);
    bool isAttackSuccessful(int successRate);
    void printStatus(const Player& player, const Boss& boss); 
};

//컨트롤러 클래스(키보드 인식 -> 움직임)
class Controller {
public:
    Controller(Player& player, Boss& boss, Map& map);
    void startGame();

private:
    Player& player;
    Boss& boss;
    Map& map;
    int playerX = 1;
    int playerY = 1;

    bool movePlayer(char input);
};

#endif