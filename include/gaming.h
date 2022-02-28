#ifndef __MY_GAMING__
#define __MY_GAMING__

#include "./struct/cast.h"

char** InitMap(int size);
struct cast RayCast(float posX, float posY, float angle, char** map, int size);

#endif