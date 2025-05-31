#include "StorySystem.h"
#include "Player.h"
#include <iostream>
#include <iomanip>
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

//���� ��� ���� (���� ��� ����)
void showEnding(const Player& player) {
    system("cls");
	double avgGPA = player.averageGPA(0); // 3���� ��� ���� ���
    cout << "====================\n";
    cout << "���� ���� : " << fixed << setprecision(2) << avgGPA << "\n";
    cout << "====================\n";
    printLine("������ �������ϴ�.....");
    if (avgGPA >= 4.0)
    {
        printLine("��������� ����Ե� ��� ���迡�� ������ �޾ҽ��ϴ�!");
        printLine("��� ���迡�� ������ ���� ��ſ��� �����Ե��� ���ڰ� ������ϴ�.");
        cout << "\n";
        Sleep(1500);
        printLine("���ǿ��� : �Ϻ��� �⸻���!");

    }
    else if (avgGPA >= 3.0)
    {
        printLine("���� ����� �����̾�����, 3���� ��� �������� �� �ƽ��ϴ�.");
        printLine("A�� �ް�, B�� �ް�.... �λ��̶� �� �׷�����.");
        printLine("���� �б⿣ ������ �븮�� �ٽ� ���θ� �����մϴ�....");
        cout << "\n";
        Sleep(1500);
        printLine("����1 : ������ �⸻���");
    }
    else if (avgGPA >= 2.0)
    {
        printLine("�������� �ں� �����ϱ��, �л��� ���� �� ������");
        printLine("������ ���迡 ����Ͽ����ϴ�....");
        printLine("������ �� �� ���θ� ������ �ϱ�....");
        cout << "\n";
        Sleep(1500);
        printLine("����2 : ����ϰ� ��ģ �⸻���");
    }
    else
    {
        printLine("���б��� Ŀ�� ������ �⼮�� Ƚ���� �������� �մϴ�.");
        printLine("�������� ���ε�, ��ġ�� �� �̻� ������ �ʾҽ��ϴ�.");
        printLine("�ᱹ ������ �б��� ������ �߽��ϴ�....");
        cout << "\n";
        Sleep(1500);
        printLine("��忣�� : �л��� 3ȸ, �����뺸.");
    }
    printLine("");
}
//���Ŀ� "���� : , ���� : " �ش� ���·� ����ϰ� �� ����
//������� ���� 3���� ������ ����� ���� ���� �б⸦ ������ �� ����