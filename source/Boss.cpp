#include "Boss.h"
//보스
Boss::Boss(const std::string& name, int maxHP, int attack, int defense)
	: Character(maxHP, attack, defense), name(name) { 
	// 보스의 체력, 공격력, 방어력 설정
}
