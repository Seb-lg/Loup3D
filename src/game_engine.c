#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../inc/conf.h"
#include "../inc/game_engine.h"
#include "../inc/struct/vector.h"

#define ABS(a) (a < 0 ? -a : a)
#define SIGN(a, b) (a < 0 && b > 0 ? -a : a > 0 && b < 0 ? -a : a)

struct cast RayCast(float posX, float posY, float angle, char **map, int size) {
  angle = angle < 0 ? angle + 360.0 : angle > 360.0 ? angle - 360.0 : angle;
  struct vector2f rayPos = makeVector2f(posX, posY);
  struct vector2f vRayDir =
      makeVector2f(cos(angle * (M_PI / 180.0)), sin(angle * (M_PI / 180.0)));
  struct vector2i vStep;
  float editMinimal = 0.001;
  int bTileFound = 0;
  struct vector2f rayHypot = makeVector2f(0, 0);
  struct vector2f rayAdd = makeVector2f(0, 0);
  int i = 100;

  vStep.x = vRayDir.x < 0 ? -1 : 1;
  vStep.y = vRayDir.y < 0 ? -1 : 1;
  while (!bTileFound && --i > 0) {
    if (vStep.x == 1) { // CAH
      rayAdd.x = (1.0 - (rayPos.x - (float)floor(rayPos.x)));
      rayHypot.x = rayAdd.x / vRayDir.x;
    } else {
      rayAdd.x = ((rayPos.x - (float)floor(rayPos.x)));
      rayHypot.x = rayAdd.x / vRayDir.x;
    }

    if (vStep.y == 1) { // SOH
      rayAdd.y = (1.0 - (rayPos.y - (float)floor(rayPos.y)));
      rayHypot.y = rayAdd.y / vRayDir.y;
    } else {
      rayAdd.y = ((rayPos.y - (float)floor(rayPos.y)));
      rayHypot.y = rayAdd.y / vRayDir.y;
    }

    if (ABS(rayHypot.x) < ABS(rayHypot.y)) {
      rayPos.x += SIGN(rayAdd.x, vStep.x) + editMinimal * vStep.x;
      rayPos.y += SIGN(vRayDir.y * rayHypot.x, vStep.y);
    } else {
      rayPos.y += SIGN(rayAdd.y, vStep.y) + editMinimal * vStep.y;
      rayPos.x += SIGN(vRayDir.x * rayHypot.y, vStep.x);
    }

    // Test tile at new test point
    if (rayPos.x >= 0 && rayPos.x < size && rayPos.y >= 0 && rayPos.y < size) {
      if (map[(int)rayPos.x][(int)rayPos.y] != ' ') {
        bTileFound = 1;
      }
    } else {
      return makeCast(-1, ' ', 0);
    }
  }

  float hitpoint;
  if (ABS(rayHypot.x) > ABS(rayHypot.y)) {
    hitpoint = ((rayPos.x - (float)floor(rayPos.x)));

  } else {
    hitpoint = ((rayPos.y - (float)floor(rayPos.y)));
  }
  return makeCast(sqrt(((rayPos.x - posX) * (rayPos.x - posX)) +
                       ((rayPos.y - posY) * (rayPos.y - posY))),
                  map[(int)rayPos.x][(int)rayPos.y], hitpoint);
}

void HandleInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    player.posX += cos(player.angle * (M_PI / 180.0)) / 10;
    player.posY += sin(player.angle * (M_PI / 180.0)) / 10;
    player.posX = player.posX < 0         ? 0
                  : player.posX > MapSize ? MapSize
                                          : player.posX;
    player.posY = player.posY < 0         ? 0
                  : player.posY > MapSize ? MapSize
                                          : player.posY;
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    player.posX -= cos(player.angle * (M_PI / 180.0)) / 10;
    player.posY -= sin(player.angle * (M_PI / 180.0)) / 10;
    player.posX = player.posX < 0         ? 0
                  : player.posX > MapSize ? MapSize
                                          : player.posX;
    player.posY = player.posY < 0         ? 0
                  : player.posY > MapSize ? MapSize
                                          : player.posY;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    player.posX -= cos((player.angle + 90.) * (M_PI / 180.0)) / 10;
    player.posY -= sin((player.angle + 90.) * (M_PI / 180.0)) / 10;
    player.posX = player.posX < 0         ? 0
                  : player.posX > MapSize ? MapSize
                                          : player.posX;
    player.posY = player.posY < 0         ? 0
                  : player.posY > MapSize ? MapSize
                                          : player.posY;
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    player.posX -= cos((player.angle - 90.) * (M_PI / 180.0)) / 10;
    player.posY -= sin((player.angle - 90.) * (M_PI / 180.0)) / 10;
    player.posX = player.posX < 0         ? 0
                  : player.posX > MapSize ? MapSize
                                          : player.posX;
    player.posY = player.posY < 0         ? 0
                  : player.posY > MapSize ? MapSize
                                          : player.posY;
  }
}
