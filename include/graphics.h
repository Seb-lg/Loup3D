#ifndef __MY_GRAPHICS__
#define __MY_GRAPHICS__


#include <GLFW/glfw3.h>

#include <stdio.h>
#include <stdlib.h>

#include "./struct/color.h"


GLFWwindow* InitGraphics(int ac, char **av);

void DrawVerticalLine(int pos, int height, struct color color);


#endif

