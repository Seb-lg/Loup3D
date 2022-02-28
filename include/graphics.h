#ifndef __MY_GRAPHICS__
#define __MY_GRAPHICS__


#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

#include "./struct/vector.h"
#include "./struct/color.h"


GLFWwindow* InitGraphics();

void DrawVerticalLine(int pos, int height, struct color color);
void DrawRectangle(struct vector2i pos, struct vector2i size, struct color color);


#endif

