#include "Boss.h"
//����
Boss::Boss(const std::string& name, int maxHP, int attack, int defense)
	: Character(maxHP, attack, defense), name(name) { 
	// ������ ü��, ���ݷ�, ���� ����
}
