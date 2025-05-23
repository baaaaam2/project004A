#include "StorySystem.h"
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

// 타이핑 효과로 한 줄 출력
void printLine(const string& line) {
    for (char c : line) {
        cout << c;
        cout.flush(); // 출력 버퍼 즉시 비움
        Sleep(1); // 40ms 대기 (0.4초)
    }
    cout << endl;
}

// 게임 시작 스토리 출력
void printStartStory(const Player& player) {
    printLine("오늘은 "+ player.name +"이(가) 속한 대학교의 중간고사의 마지막 날이다.");
    printLine("" + player.name + "는 오늘 무려 3개의 시험을 치지만 공부를 하지 않아 시험을 망칠 위기에 처하게 되는데");
    printLine("전날 부랴부랴 벼락치기를 했지만 결국 공부를 다 마치치 못한체 학교로 향하게 되는데....");
    cout << "(계속하려면 아무 키나 누르세요...)\n";
    _getch(); // 키 입력 대기
}

// 보스 조우 스토리 출력
void printBossEncounterStory(const Player& player) {
    printLine("교실로 들어가 자리에 앉으니 교수님이 시험지를 들고 다가옵니다.");
    printLine("이 문제들을 풀 수 있겠나, " + player.name + "?");
    printLine("전투가 시작됩니다!");
    cout << "(계속하려면 아무 키나 누르세요...)\n";
    _getch(); // 키 입력 대기
}

// 승리 스토리 출력
void printWinStory(const Player& player) {
    printLine("축하합니다! 시험을 통과했습니다!");
    printLine("교수님은 시험지를 걷어가며 만족한 듯 미소를 짓습니다.");
    printLine("교수님 : \"시험공부를 많이 했나보군.\"");
    cout << "(계속하려면 아무 키나 누르세요...)\n";
    _getch(); // 키 입력 대기
}

// 패배 스토리 출력
void printLoseStory(const Player& player) {
    printLine("아쉽게도 시험에서 패배했습니다...");
    printLine("교수님이 시험지를 걷어가며 만족하지 못한듯 표정을 찡그립니다.");
    printLine("교수님 : \"이 쉬운 시험을 통과를 못하다니....\"");
    cout << "(계속하려면 아무 키나 누르세요...)\n";
    _getch(); // 키 입력 대기
}

//엔딩 출력 예시
void showEnding(const Player& player, char grade) {
    system("cls");
    cout << "게임 종료\n";
    cout << "====================\n";
    cout << player.name << "님은 " << grade << "을 받았습니다!\n";
    cout << "====================\n";
}
//추후에 "과목 : , 점수 : " 해당 형태로 출력하게 할 것임
//엔딩출력 또한 3개의 과목을 평균을 내서 엔딩 분기를 나누게 할 것임