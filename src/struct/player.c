#include "../../include/struct/player.h"

struct player InitPlayer() {
    struct player player;

    player.posX = 10;
    player.posY = 10;

    player.angle = 0;

    return player;
}