#include "StorySystem.h"
#include "Player.h"
#include <iostream>
#include <iomanip>
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

//엔딩 출력 예시 (학점 출력 수정)
void showEnding(const Player& player) {
    system("cls");
	double avgGPA = player.averageGPA(0); // 3과목 평균 학점 계산
    cout << "====================\n";
    cout << "최종 학점 : " << fixed << setprecision(2) << avgGPA << "\n";
    cout << "====================\n";
    printLine("시험이 끝났습니다.....");
    if (avgGPA >= 4.0)
    {
        printLine("어려웠지만 놀랍게도 모든 시험에서 만점을 받았습니다!");
        printLine("모든 시험에서 만점을 받은 당신에게 교수님들의 문자가 쏟아집니다.");
        cout << "\n";
        Sleep(1500);
        printLine("해피엔딩 : 완벽한 기말고사!");

    }
    else if (avgGPA >= 3.0)
    {
        printLine("아주 어려운 시험이었지만, 3과목 모두 생각보다 잘 쳤습니다.");
        printLine("A도 받고, B도 받고.... 인생이란 다 그런거죠.");
        printLine("다음 학기엔 만점을 노리며 다시 공부를 시작합니다....");
        cout << "\n";
        Sleep(1500);
        printLine("엔딩1 : 무난한 기말고사");
    }
    else if (avgGPA >= 2.0)
    {
        printLine("교수님의 자비 덕분일까요, 학사경고를 받을 뻔 했지만");
        printLine("간신히 시험에 통과하였습니다....");
        printLine("다음엔 좀 더 공부를 열심히 하길....");
        cout << "\n";
        Sleep(1500);
        printLine("엔딩2 : 평범하게 못친 기말고사");
    }
    else
    {
        printLine("장학금은 커녕 수업에 출석한 횟수도 가물가물 합니다.");
        printLine("교수님의 연민도, 눈치도 더 이상 통하지 않았습니다.");
        printLine("결국 조용히 학교를 떠나야 했습니다....");
        cout << "\n";
        Sleep(1500);
        printLine("배드엔딩 : 학사경고 3회, 제적통보.");
    }
    printLine("");
}
//추후에 "과목 : , 점수 : " 해당 형태로 출력하게 할 것임
//엔딩출력 또한 3개의 과목을 평균을 내서 엔딩 분기를 나누게 할 것임