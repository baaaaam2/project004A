#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

class Item {
private:
    string name;
    int price;
    int attackPlus; //공격력 더하기
    int defensePlus; //방어력 더하기
    int healAmount; // 회복 아이템일 경우

public:
    Item(string name, int price, int attackPlus, int defensePlus, int healAmount);

    string getName() const;
    int getPrice() const;
    int getHealAmount() const;
    int getAttackPlus() const;
    int getDefensePlus() const;

};

#endif#pragma once
