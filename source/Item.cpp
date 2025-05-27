#include "Item.h"

using namespace std;

//추후에 (이름, 가격, 공격력, 방어력, 힐)으로 수정할 것
Item::Item(string name, int price, int attackPlus, int defensePlus, int healAmount)
    : name(name), price(price), attackPlus(attackPlus), defensePlus(defensePlus), healAmount(healAmount) {
}

string Item::getName() const {
    return name;
}

int Item::getPrice() const {
    return price;
}

int Item::getHealAmount() const {
    return healAmount;
}
int Item::getAttackPlus() const {
    return attackPlus;
}
int Item::getDefensePlus() const {
    return defensePlus;
}

