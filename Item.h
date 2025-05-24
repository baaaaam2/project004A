#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

class Item {
private:
    string name;
    int price;
    int healAmount; // ȸ�� �������� ���

public:
    Item(string name, int price, int healAmount);

    string getName() const;
    int getPrice() const;
    int getHealAmount() const;
};

#endif#pragma once
