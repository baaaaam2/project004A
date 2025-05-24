#ifndef STORY_SYSTEM_H
#define STORY_SYSTEM_H

#include <string>
#include "Player.h" // Player ��ü�� �Ű������� ����ϱ� ���� ����

// ���丮 ��� �Լ�
void printStartStory(const Player& player);
void printBossEncounterStory(const Player& player);
void printWinStory(const Player& player);
void printLoseStory(const Player& player);

// Ÿ���� �Լ�
void printLine(const string& line);

//���� ��� �Լ�
void showEnding(const Player& player, char grade);

#endif