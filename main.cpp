#include <vector>
#include "Map.h"
#include "Player.h"
#include "Boss.h"
#include "Controller.h"

using namespace std;

int main() {
	vector<Boss> bosses;
	bosses.emplace_back("���ڵ� ������", 100, 40, 10); // ���� ����
	bosses.emplace_back("����ü ������", 100, 50, 5); // ���� ����
	bosses.emplace_back("�ڰ��� ������", 100, 30, 30); // ���� ����
	bosses.emplace_back("ģ��1", 80, 20, 1); // �߰� ���� ����
	bosses.emplace_back("ģ��2", 80, 10, 3); // �߰� ���� ����
	bosses.emplace_back("ģ��3", 80, 5, 5); // �߰� ���� ����
	Map map;
	Player player("", 100, 30);
	Controller controller(player, bosses, map);
	controller.startGame();
	return 0;
}
