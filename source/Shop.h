#ifndef SHOP_H
#define SHOP_H

#include "Item.h"
#include "Player.h"
#include <iostream>
#include <vector>

class Shop {
private:
    vector<Item> shopItems;

    void showMenu(Player& player); //메뉴 선택 출력
    void handleInput(); //입력 감지
public:
    Shop();
    void enterShop(Player& player ); //상점 입장
    void buyItem(Player& player); //아이템 구매 입장
};

#endif
