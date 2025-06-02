ï»?#include "Controller.h"
#include "Player.h"
#include "BattleSystem.h"
#include "StorySystem.h"
#include "Shop.h"
#include <iostream>
#include <conio.h>
#include <ctime>
#include <windows.h>

using namespace std;

Controller::Controller(Player& player, vector<Boss> bosses, Map& map)
    : player(player), bosses(move(bosses)), map(map), defeatedBosses(this->bosses.size(), false) {

    // êµìˆ˜?‹˜ ë³´ìŠ¤ 3ëª…ì˜ ê³ ì • ì¢Œí‘œ ì§?? •
    bossMap[{21, 2}] = 0;  // ê¹?ì½”ë”© êµìˆ˜?‹˜
    bossMap[{6, 14}] = 1;  // ì¡°ê°ì²? êµìˆ˜?‹˜
    bossMap[{24, 18}] = 2; // ë°•ê²Œ?„ êµìˆ˜?‹˜
}

int Controller::getRemainingBossCount() const
{
    int count = 0;
    for (size_t i = 0; i < bosses.size(); ++i) {
        if (!defeatedBosses[i] && bosses[i].name.find("êµìˆ˜?‹˜") != string::npos) { // êµìˆ˜?‹˜ ?´ë¦„ì´ ?¬?•¨?œ ë³´ìŠ¤ë§? ì¹´ìš´?Š¸
            count++;
        }
    }
    return count;
}

void Controller::startGame()
{
    srand(static_cast<unsigned>(time(0)));
    cout << "ì£¼ì¸ê³µì˜ ?´ë¦„ì„ ?…? ¥?•˜?„¸?š” : ";
    getline(cin, player.name); //?”Œ? ˆ?´?–´ ?´ë¦? ?„¤? •
    system("cls");
    printStartStory(player); // StorySystem.h?—?„œ ?˜¸ì¶?

    map.initialize();
    for (const auto& entry : bossMap) { // ë³´ìŠ¤ ?œ„ì¹? ?„¤? •
        map.setTile(entry.first.first, entry.first.second, 'B');
    }
    char input;
    bool running = true;

    while (running)
    {
        map.print(player, playerX, playerY, getRemainingBossCount());
        input = _getch();

        if (input == 'q' || input == 'Q') //q ?…? ¥?‹œ ì¢…ë£Œ
        {
            running = false;
        }
        else if (movePlayer(input))
        {
            pair<int, int> currentPos = { playerX, playerY };
            if (map.getTile(playerX, playerY) == 'S') //?ƒ?  ?…?¥
            {
                Shop shop;
                shop.enterShop(player);
            }
            if (bossMap.count(currentPos)) { 
                int bossIndex = bossMap[currentPos];

                if (!defeatedBosses[bossIndex]) {
                    printBossEncounterStory(player);
                    BattleSystem bs;
                    bs.fight(player, bosses[bossIndex]);

                    defeatedBosses[bossIndex] = true;
                    map.setTile(playerX, playerY, ' ');
                    if (bosses[bossIndex].isDead()) {
                        cout << "\n";
						cout << bosses[bossIndex].getName() << " ?„(ë¥?) ì²˜ì¹˜?–ˆ?Šµ?‹ˆ?‹¤!\n" << endl;
						printWinStory(player);
                    }
                    else {
						cout << "\n";
                        cout << bosses[bossIndex].getName() << " ê³¼ì˜ ? „?ˆ¬?—?„œ ?Œ¨ë°°í–ˆ?Šµ?‹ˆ?‹¤...\n" << endl;
                        printLoseStory(player);
                    }
					// ë³´ìŠ¤ ? „?ˆ¬ ?›„ ?”Œ? ˆ?´?–´ê°? ì£½ì?? ê²½ìš°
                    if (getRemainingBossCount() != 0 && player.isDead()) {
						system("cls");
                        printLine("?”Œ? ˆ?´?–´ê°? ê¸°ì ˆ?–ˆ?‹¤ê°? ê¸°ìˆ™?‚¬?—?„œ ê¹¨ì–´?‚¬?Šµ?‹ˆ?‹¤..\n");
                        cout << "(ê³„ì†?•˜? ¤ë©? ?•„ë¬? ?‚¤?‚˜ ?ˆ„ë¥´ì„¸?š”...)\n";
                        _getch(); // ?‚¤ ?…? ¥ ???ê¸?
						player.hp = player.maxHP; // ?”Œ? ˆ?´?–´ ì²´ë ¥ ?šŒë³?
						playerX = 1; // ?”Œ? ˆ?´?–´ ?œ„ì¹? ì´ˆê¸°?™”
						playerY = 1; // ?”Œ? ˆ?´?–´ ?œ„ì¹? ì´ˆê¸°?™”
                        continue;
                    }
                }
            }

            if (getRemainingBossCount() <= 0) // ëª¨ë“  êµìˆ˜?‹˜?„ ì²˜ì¹˜?•œ ê²½ìš°(?‹œ?—˜?„ ëª¨ë‘ ?‘¼ ê²½ìš°)
            {
                showEnding(player);
                running = false;
            }
        }
    }
    
    cout << "\nê²Œì„ ì¢…ë£Œ!" << endl;
	cout << "?‹œ?—˜ì¹˜ëŠ?¼ ê³ ìƒ?•˜?…¨?Šµ?‹ˆ?‹¤!\n";
}

bool Controller::movePlayer(char input) 
{
    int newX = playerX, newY = playerY;
    switch (input) {
    case 'w': case 'W': newY--; break; //w,W ?…? ¥?‹œ Y-1 (?œ„ë¡?)
    case 's': case 'S': newY++; break; //s,S ?…? ¥?‹œ Y+1 (ë°‘ìœ¼ë¡?)
    case 'a': case 'A': newX--; break; //a,A ?…? ¥?‹œ X-1 (?™¼ìª½ìœ¼ë¡?)
    case 'd': case 'D': newX++; break; //d,D ?…? ¥?‹œ X+1 (?˜¤ë¥¸ìª½?œ¼ë¡?)
    default: return false;
    }

    char tile = map.getTile(newX, newY);
    // ?´?™ ê°??Š¥?•œ ????¼ë§? ?—ˆ?š© (ê³µë°± ?˜?Š” 'S' ?œ„ì¹? ?“±)
    if (tile == ' ' || tile == 'S' || tile =='B') {
        playerX = newX;
        playerY = newY;

        int chance = rand() % 100;
        if (chance < 0) { // ?˜„?¬?Š” ?•­?ƒ ?‹¤?–‰ ?•ˆ ?¨ (?™•ë¥? ì¡°ê±´ ?ˆ˜? • ?•„?š”)
            int friendindex = 3 + rand() % 3;
            std::cout << bosses[friendindex].name << "???(ê³?) ì¡°ìš°?–ˆ?Šµ?‹ˆ?‹¤!\n";
            BattleSystem bs;
            bs.fightfriend(player, bosses[friendindex]);
            bosses[friendindex].hp = bosses[friendindex].maxHP;
            Sleep(1500);
            if (getRemainingBossCount() != 0 && player.isDead()) 
            {
                system("cls");
                printLine("ÇÃ·¹ÀÌ¾î°¡ ±âÀıÇß´Ù°¡ ±â¼÷»ç¿¡¼­ ±ú¾î³µ½À´Ï´Ù..\n");
                cout << "(°è¼ÓÇÏ·Á¸é ¾Æ¹« Å°³ª ´©¸£¼¼¿ä...)\n";
                _getch(); // Å° ÀÔ·Â ´ë±â
                player.hp = player.maxHP; // ÇÃ·¹ÀÌ¾î Ã¼·Â È¸º¹
                playerX = 1; // ÇÃ·¹ÀÌ¾î À§Ä¡ ÃÊ±âÈ­
                playerY = 1; // ÇÃ·¹ÀÌ¾î À§Ä¡ ÃÊ±âÈ­
            }
        }

        return true;
    }

    return false;
}
