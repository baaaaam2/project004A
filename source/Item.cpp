#include "Item.h"

using namespace std;

Item::Item(string name, int price, int healAmount)
    : name(name), price(price), healAmount(healAmount) {
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
