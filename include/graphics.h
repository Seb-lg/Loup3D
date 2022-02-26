#ifndef __MY_GRAPHICS__
#define __MY_GRAPHICS__


#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


void InitGraphics(int ac, char **av, void*);

void DrawLine(int x, int y, int a, int b);


#endif

