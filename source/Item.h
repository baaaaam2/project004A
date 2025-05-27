#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

class Item {
private:
    string name;
    int price;
    int attackPlus; //���ݷ� ���ϱ�
    int defensePlus; //���� ���ϱ�
    int healAmount; // ȸ�� �������� ���

public:
    Item(string name, int price, int attackPlus, int defensePlus, int healAmount);

    string getName() const;
    int getPrice() const;
    int getHealAmount() const;
    int getAttackPlus() const;
    int getDefensePlus() const;

};

#endif#pragma once
