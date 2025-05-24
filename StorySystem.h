#ifndef STORY_SYSTEM_H
#define STORY_SYSTEM_H

#include <string>
#include "Player.h" // Player 객체를 매개변수로 사용하기 위해 포함

// 스토리 출력 함수
void printStartStory(const Player& player);
void printBossEncounterStory(const Player& player);
void printWinStory(const Player& player);
void printLoseStory(const Player& player);

// 타이핑 함수
void printLine(const string& line);

//엔딩 출력 함수
void showEnding(const Player& player, char grade);

#endif