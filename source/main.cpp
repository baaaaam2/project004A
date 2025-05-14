#include "game.h"

int main() {
    Map map;
    Player player("");
    Boss boss;
    Controller controller(player, boss, map);
    controller.startGame();
    return 0;
}
