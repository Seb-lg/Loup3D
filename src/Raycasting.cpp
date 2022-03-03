//
// Created by seub on 3/3/22.
//

#include "Raycasting.hpp"
#include <vector>
#include <cmath>

#define ABS(a) (a < 0 ? -a : a)
#define SIGN(a, b) (a < 0 && b > 0 ? -a : a > 0 && b < 0 ? -a : a)

Raycasting::cast Raycasting::getHeight(std::shared_ptr<Player> &player, float angle, std::shared_ptr<Map> &map) {
    static std::vector<float> rayPos = {0, 0};
    static std::vector<float> vRayDir = {0, 0};
    static std::vector<float> vStep = {0,0};
    static std::vector<float> rayHypot = {0, 0};
    static std::vector<float> rayAdd = {0, 0};

    angle = angle < 0 ? angle + 360.f : angle > 360.f ? angle - 360.f : angle;
     rayPos = {player->posX, player->posY};
     vRayDir = {cosf(angle * (M_PIf / 180.f)), sinf(angle * (M_PIf / 180.f))};
     vStep = {0,0};
    float editMinimal = 0.00001;
    int bTileFound = 0;
     rayHypot = {0, 0};
     rayAdd = {0, 0};

    vStep[0] = vRayDir[0] < 0.f ? -1 : 1;
    vStep[1] = vRayDir[1] < 0.f ? -1 : 1;

    while (!bTileFound ) {
        if (vStep[0] == 1) { // CAH
            rayAdd[0] = 1.f - (rayPos[0] - (float) floor(rayPos[0]));
            rayHypot[0] = rayAdd[0] / vRayDir[0];
        } else {
            rayAdd[0] = ((rayPos[0] - (float) floor(rayPos[0])));
            rayHypot[0] = rayAdd[0] / vRayDir[0];
        }

        if (vStep[1] == 1) { // SOH
            rayAdd[1] = 1.f - (rayPos[1] - (float) floorf(rayPos[1]));
            rayHypot[1] = rayAdd[1] / vRayDir[1];
        } else {
            rayAdd[1] = ((rayPos[1] - (float) floor(rayPos[1])));
            rayHypot[1] = rayAdd[1] / vRayDir[1];
        }
        // Choose the smallest hypotenuse and increment other dimension
        if (ABS(rayHypot[0]) < ABS(rayHypot[1])) {
            rayPos[0] += SIGN(rayAdd[0], vStep[0]) + editMinimal * vStep[0];
            rayPos[1] += SIGN(vRayDir[1] * rayHypot[0], vStep[1]);
        } else {
            rayPos[1] += SIGN(rayAdd[1], vStep[1]) + editMinimal * vStep[1];
            rayPos[0] += SIGN(vRayDir[0] * rayHypot[1], vStep[0]);
        }

        // Look on the map if the new position is a wall
        if (rayPos[0] >= 0 && rayPos[0] < map->width && rayPos[1] >= 0 && rayPos[1] < map->height) {
            if ((*map)[(int)rayPos[0]][(int) rayPos[1]] != ' ') {
                bTileFound = 1;
            }
        } else {
//            exit(0);
            return {-1, ' ', 0};
        }
    }
    int hitDirection = ABS(rayHypot[0]) < ABS(rayHypot[1]);
//    exit(0);
    return {
        .distance = sqrtf((powf(rayPos[0] - player->posX,2) + powf(rayPos[1] - player->posY,2.f))),
        .type = (*map)[(int)rayPos[0]][(int)rayPos[1]],
        .hitpoint = rayPos[hitDirection] - (float)floor(rayPos[hitDirection])
    };
}

void
Raycasting::drawMap(std::shared_ptr<Graphic> &window, std::shared_ptr<Player> &player, std::shared_ptr<Map> &map) {
    for (int i = 0; i < window->width; ++i) {
        float angleForCast = player->angle - (window->fov / 2) + ((window->fov / (float) window->width) * (float) i);
        cast value = Raycasting::getHeight(player, angleForCast, map);

        if (value.distance == -1.0) continue;

        value.distance = value.distance * cos((player->angle - angleForCast) * (M_PI / 180.0));
        value.distance = window->height / value.distance;

        window->drawVerticalLineWithTexture(i, value.distance, player, window->textures[value.type].data(),
                                    800 * value.hitpoint, 800);
    }
}
