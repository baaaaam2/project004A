#include "Shop.h"
#include "Item.h"
#include "Map.h"
#include "Player.h"
#include <windows.h>

using namespace std;

Shop::Shop() {
    // ������ �ʱ�ȭ
    shopItems.push_back(Item("����å", 1500, 120, 100, 100)); //���� : 1500��, ���ݷ� : 120% = 120, ���� : 0, �� : 0
    shopItems.push_back(Item("����", 1000, 110, 100, 100)); //���� : 1000��, ���ݷ� : 110% = 110, ���� : 0, �� : 0
    shopItems.push_back(Item("�޴���", 4000, 130, 100, 100)); //���� : 4000��, ���ݷ� : 130% = 130, ���� : 0, �� : 0
    shopItems.push_back(Item("����", 2000, 100, 100, 30));  //���� : 2000��, ���ݷ� :          0, ���� : 0, �� : 30
}

//���� ���� �� ���� �⺻ ����
void Shop::enterShop(Player& player) {
    bool inShop = true;
    while (inShop) {
        system("cls");
        cout << "\n";
        cout << "==========================\n";
        cout << "    ������ ���Խ��ϴ�!   \n";
        cout << "==========================\n";
        cout << " ���� �ܾ� : " << player.getGold() << "��\n";
        cout << " ���� ü�� : " << player.hp << " / " << player.maxHP << " HP\n";
        cout << " ���� ���ݷ� : " << player.attack << "%\n";
        cout << " ���� ���� : " << player.defense << "%\n";
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
            cout << "\n�������� �����ϴ�.\n";
            Sleep(2000);
            inShop = false;
            break;
        default:
            cout << "�߸��� �����Դϴ�. �ٽ� �Է��ϼ���.\n";
            Sleep(2000);
            break;
        }
    }
}


void Shop::showMenu(Player& player) {
    cout << "1. ������ ����\n";
    cout << "2. ���� ������\n";
    cout << "���� : ";
}

void Shop::buyItem(Player& player)
{
    //������ 1������ n��° ������ ���� ����
    //�������� ���������� ������ �̸� ���� (���ſϷ�)��� ���
    cout << "\n�Ǹ� ���� ������ : \n";
    for (size_t i = 0; i < shopItems.size(); ++i)
    {
        const Item& item = shopItems[i];
        cout << i + 1 << ". " << shopItems[i].getName() << " : " << shopItems[i].getPrice() << "��";
        if (i == 3) { // 4�� ���� ������ (0-based �ε���)
            cout << " [����: " << player.getMonsterItemCount() << "/5]";
        }
        if (item.getHealAmount() == 0 && player.isItemPurchased(i + 1)) {
            cout << "(���ſϷ�)";
        }
        cout << "\n";
    }
    //������ ���� + 1 ���ý� �����޴��� ���ư���
    cout << (shopItems.size() + 1) << ". ���ư���\n";
    cout << "���� : ";

    int choice;
    cin >> choice;
    int index = choice - 1;
    Item item = shopItems[index];

    //������, ���ư��� �̿��� �Է� ������ ���
    if (choice < 1 || choice > shopItems.size() + 1)
    {
        cout << "�߸��� �����Դϴ�. �ٽ� �Է��ϼ���.\n";
        Sleep(2000);
        return;
    }

    //�������� �������� +1�� ���� �Է½� ���ư���
    if (choice == shopItems.size() + 1)
    {
        return;
    }

    //������ ������ �ν�
    if (item.getHealAmount() == 0 && player.isItemPurchased(choice)) {
        cout << "\n�̹� ������ �������Դϴ�.\n";
        Sleep(2000);
        return;
    }

    //�ܾ� ���� �ν�
    if (player.getGold() < item.getPrice()) {
        cout << "\n�ܾ��� �����մϴ�.\n";
        Sleep(2000);
        cout << "���� �� ���� �������ּ���.\n";
        Sleep(2000);
        return;
    }

    if (choice == 4) //���� ������ ����
    {
        if (player.getMonsterItemCount() >= 5)
        {
            cout << "\n�� �������� �ִ� 5������ ������ �� �ֽ��ϴ�.\n";
            Sleep(2000);
            return;
        }

        if (player.getGold() < item.getPrice()) {
            cout << "\n�ܾ��� �����մϴ�.\n";
            Sleep(2000);
            return;
        }

        player.addGold(-item.getPrice());
        player.addMonsterItem();
        player.addAttackMultiplier(item.getAttackPlus());

        cout << "\n" << item.getName() << "��(��) �����߽��ϴ�.\n";
        Sleep(1000);
        cout << item.getPrice() << "���� �����˴ϴ�.\n";
        Sleep(1000);
        cout << "���� ������ ���� ����: " << player.getMonsterItemCount() << "/5\n";
        Sleep(1500);
        return;
    }
    //���� �� �ܾ� ����
    cout << "\n" << item.getName() << "��(��) �����߽��ϴ�.\n";
    Sleep(2000);
    cout << item.getPrice() << "���� �����˴ϴ�.\n";
    Sleep(2000);
    player.addGold(-item.getPrice());

    //if ü�� ȸ�� ������ ���
    //else ���� ������ ����
    ///*if (item.getHealAmount() > 0) {
    //    player.addHp(item.getHealAmount());
    //    cout << "ü���� " << item.getHealAmount() << " ȸ���˴ϴ�.\n";
    //    Sleep(2000);

    if (item.getHealAmount() == 0)
    {
        player.purchaseItem(choice);
        player.addAttackMultiplier(item.getAttackPlus());   //�⺻ ���ݷ� + ������ ���ݷ�
        player.addDefenseMultiplier(item.getDefensePlus()); //�⺻ ���� + ������ ����
    }

}
