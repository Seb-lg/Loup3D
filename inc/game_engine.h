#ifndef __MY_GAMING__
#define __MY_GAMING__

#include <GLFW/glfw3.h>

#include "./struct/cast.h"

char **InitMap(int size);

struct cast RayCast(float posX, float posY, float angle, char **map, int size);

void HandleInput(GLFWwindow *);

#endif
