#include "Shop.h"
#include "Item.h"
#include "Map.h"
#include "Player.h"
#include <windows.h>

using namespace std;

Shop::Shop() {
    // 아이템 초기화
    shopItems.push_back(Item("전공책", 1500, 120, 100, 100)); //가격 : 1500원, 공격력 : 120% = 120, 방어력 : 0, 힐 : 0
    shopItems.push_back(Item("계산기", 1000, 110, 100, 100)); //가격 : 1000원, 공격력 : 110% = 110, 방어력 : 0, 힐 : 0
    shopItems.push_back(Item("휴대폰", 4000, 130, 100, 100)); //가격 : 4000원, 공격력 : 130% = 130, 방어력 : 0, 힐 : 0
    shopItems.push_back(Item("몬스터", 2000, 100, 100, 30));  //가격 : 2000원, 공격력 :          0, 방어력 : 0, 힐 : 30
}

//상점 입장 및 상점 기본 구성
void Shop::enterShop(Player& player) {
    bool inShop = true;
    while (inShop) {
        system("cls");
        cout << "\n";
        cout << "==========================\n";
        cout << "    상점에 들어왔습니다!   \n";
        cout << "==========================\n";
        cout << " 현재 잔액 : " << player.getGold() << "원\n";
        cout << " 현재 체력 : " << player.hp << " / " << player.maxHP << " HP\n";
        cout << " 현재 공격력 : " << player.attack << "%\n";
        cout << " 현재 방어력 : " << player.defense << "%\n";
        cout << "==========================\n";

        showMenu(player);

        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
            buyItem(player);
            break;
        case 2:
            cout << "\n상점에서 나갑니다.\n";
            Sleep(2000);
            inShop = false;
            break;
        default:
            cout << "잘못된 선택입니다. 다시 입력하세요.\n";
            Sleep(2000);
            break;
        }
    }
}


void Shop::showMenu(Player& player) {
    cout << "1. 아이템 구매\n";
    cout << "2. 상점 나가기\n";
    cout << "선택 : ";
}

void Shop::buyItem(Player& player)
{
    //아이템 1번부터 n번째 아이템 까지 나열
    //아이템을 구매했으면 아이템 이름 옆에 (구매완료)라고 출력
    cout << "\n판매 중인 아이템 : \n";
    for (size_t i = 0; i < shopItems.size(); ++i)
    {
        const Item& item = shopItems[i];
        cout << i + 1 << ". " << shopItems[i].getName() << " : " << shopItems[i].getPrice() << "원";
        if (i == 3) { // 4번 몬스터 아이템 (0-based 인덱스)
            cout << " [보유: " << player.getMonsterItemCount() << "/5]";
        }
        if (item.getHealAmount() == 0 && player.isItemPurchased(i + 1)) {
            cout << "(구매완료)";
        }
        cout << "\n";
    }
    //아이템 갯수 + 1 선택시 이전메뉴로 돌아가기
    cout << (shopItems.size() + 1) << ". 돌아가기\n";
    cout << "선택 : ";

    int choice;
    cin >> choice;
    int index = choice - 1;
    Item item = shopItems[index];

    //아이템, 돌아가기 이외의 입력 받을시 출력
    if (choice < 1 || choice > shopItems.size() + 1)
    {
        cout << "잘못된 선택입니다. 다시 입력하세요.\n";
        Sleep(2000);
        return;
    }

    //아이템의 갯수보다 +1인 숫자 입력시 돌아가기
    if (choice == shopItems.size() + 1)
    {
        return;
    }

    //구매한 아이템 인식
    if (item.getHealAmount() == 0 && player.isItemPurchased(choice)) {
        cout << "\n이미 구매한 아이템입니다.\n";
        Sleep(2000);
        return;
    }

    //잔액 부족 인식
    if (player.getGold() < item.getPrice()) {
        cout << "\n잔액이 부족합니다.\n";
        Sleep(2000);
        cout << "돈을 더 벌고 구매해주세요.\n";
        Sleep(2000);
        return;
    }

    if (choice == 4) //몬스터 아이템 구매
    {
        if (player.getMonsterItemCount() >= 5)
        {
            cout << "\n이 아이템은 최대 5개까지 구매할 수 있습니다.\n";
            Sleep(2000);
            return;
        }

        if (player.getGold() < item.getPrice()) {
            cout << "\n잔액이 부족합니다.\n";
            Sleep(2000);
            return;
        }

        player.addGold(-item.getPrice());
        player.addMonsterItem();
        player.addAttackMultiplier(item.getAttackPlus());

        cout << "\n" << item.getName() << "을(를) 구매했습니다.\n";
        Sleep(1000);
        cout << item.getPrice() << "원이 차감됩니다.\n";
        Sleep(1000);
        cout << "몬스터 아이템 보유 수량: " << player.getMonsterItemCount() << "/5\n";
        Sleep(1500);
        return;
    }
    //구매 및 잔액 차감
    cout << "\n" << item.getName() << "을(를) 구매했습니다.\n";
    Sleep(2000);
    cout << item.getPrice() << "원이 차감됩니다.\n";
    Sleep(2000);
    player.addGold(-item.getPrice());

    //if 체력 회복 아이템 사용
    //else 영구 아이템 구매
    ///*if (item.getHealAmount() > 0) {
    //    player.addHp(item.getHealAmount());
    //    cout << "체력이 " << item.getHealAmount() << " 회복됩니다.\n";
    //    Sleep(2000);

    if (item.getHealAmount() == 0)
    {
        player.purchaseItem(choice);
        player.addAttackMultiplier(item.getAttackPlus());   //기본 공격력 + 아이템 공격력
        player.addDefenseMultiplier(item.getDefensePlus()); //기본 방어력 + 아이템 방어력
    }

}
