#include <vector>
#include "Map.h"
#include "Player.h"
#include "Boss.h"
#include "Controller.h"

using namespace std;

int main() {
	vector<Boss> bosses;
	bosses.emplace_back("김코딩 교수님", 100, 40, 10); // 보스 생성
	bosses.emplace_back("조객체 교수님", 100, 50, 5); // 보스 생성
	bosses.emplace_back("박게임 교수님", 100, 30, 30); // 보스 생성
	bosses.emplace_back("친구1", 80, 20, 1); // 중간 보스 생성
	bosses.emplace_back("친구2", 80, 10, 3); // 중간 보스 생성
	bosses.emplace_back("친구3", 80, 5, 5); // 중간 보스 생성
	Map map;
	Player player("", 100, 30);
	Controller controller(player, bosses, map);
	controller.startGame();
	return 0;
}
