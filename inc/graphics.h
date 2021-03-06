#ifndef __MY_GRAPHICS__
#define __MY_GRAPHICS__

#include "./struct/color.h"
#include "./struct/vector.h"
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

GLFWwindow *InitGraphics();

void DrawVerticalLine(int pos, int height, struct color color);
void DrawVerticalLineWithTexture(int pos, int height, unsigned char *img,
                                 int texture_pos, int texture_height);
void DrawRectangle(struct vector2i pos, struct vector2i size,
                   struct color color);

unsigned char *load_bmp(char *path, int *width, int *height);

#endif
