#include "StorySystem.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

// Ÿ���� ȿ���� �� �� ���
void printLine(const string& line) {
    for (char c : line) {
        cout << c;
        cout.flush(); // ��� ���� ��� ���
        Sleep(1); // 40ms ��� (0.4��)
    }
    cout << endl;
}

// ���� ���� ���丮 ���
void printStartStory(const Player& player) {
    printLine("������ "+ player.name +"��(��) ���� ���б��� �߰������ ������ ���̴�.");
    printLine("" + player.name + "�� ���� ���� 3���� ������ ġ���� ���θ� ���� �ʾ� ������ ��ĥ ���⿡ ó�ϰ� �Ǵµ�");
    printLine("���� �η��η� ����ġ�⸦ ������ �ᱹ ���θ� �� ��ġġ ����ü �б��� ���ϰ� �Ǵµ�....");
    cout << "(����Ϸ��� �ƹ� Ű�� ��������...)\n";
    _getch(); // Ű �Է� ���
}

// ���� ���� ���丮 ���
void printBossEncounterStory(const Player& player) {
    printLine("���Ƿ� �� �ڸ��� ������ �������� �������� ��� �ٰ��ɴϴ�.");
    printLine("�� �������� Ǯ �� �ְڳ�, " + player.name + "?");
    printLine("������ ���۵˴ϴ�!");
    cout << "(����Ϸ��� �ƹ� Ű�� ��������...)\n";
    _getch(); // Ű �Է� ���
}

// �¸� ���丮 ���
void printWinStory(const Player& player) {
    printLine("�����մϴ�! ������ ����߽��ϴ�!");
    printLine("�������� �������� �Ⱦ�� ������ �� �̼Ҹ� �����ϴ�.");
    printLine("������ : \"������θ� ���� �߳�����.\"");
    cout << "(����Ϸ��� �ƹ� Ű�� ��������...)\n";
    _getch(); // Ű �Է� ���
}

// �й� ���丮 ���
void printLoseStory(const Player& player) {
    printLine("�ƽ��Ե� ���迡�� �й��߽��ϴ�...");
    printLine("�������� �������� �Ⱦ�� �������� ���ѵ� ǥ���� ���׸��ϴ�.");
    printLine("������ : \"�� ���� ������ ����� ���ϴٴ�....\"");
    cout << "(����Ϸ��� �ƹ� Ű�� ��������...)\n";
    _getch(); // Ű �Է� ���
}

//���� ��� ����
void showEnding(const Player& player, char grade) {
    system("cls");
    cout << "���� ����\n";
    cout << "====================\n";
    cout << player.name << "���� " << grade << "�� �޾ҽ��ϴ�!\n";
    cout << "====================\n";
}
//���Ŀ� "���� : , ���� : " �ش� ���·� ����ϰ� �� ����
//������� ���� 3���� ������ ����� ���� ���� �б⸦ ������ �� ����