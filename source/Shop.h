#ifndef SHOP_H
#define SHOP_H

#include "Item.h"
#include "Player.h"
#include <iostream>
#include <vector>

class Shop {
private:
    vector<Item> shopItems;

    void showMenu(Player& player); //�޴� ���� ���
    void handleInput(); //�Է� ����
public:
    Shop();
    void enterShop(Player& player ); //���� ����
    void buyItem(Player& player); //������ ���� ����
};

#endif
