#include "../include/graphics.h"

void InitGraphics(int ac, char **av, void *display) {

    // Use a single buffered window in RGB mode (as opposed to a double-buffered
    // window or color-index mode).
    glutInit(&ac, av);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    // Position window at (80,80)-(480,380) and give it a title.
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(400, 300);
    glutCreateWindow("A Simple Triangle");

    // Tell GLUT that whenever the main window needs to be repainted that it
    // should call the function display().
    glutDisplayFunc(display);

    // Tell GLUT to start reading and processing events.  This function
    // never returns; the program only exits when the user closes the main
    // window or kills the process.
    glutMainLoop();
}

void DrawLine(int x, int y, int a, int b) {
    glBegin(GL_LINES);
        glColor3f(1,0,1);glVertex2i(1,0);
        glColor3f(1,1,1);glVertex2i(0,1);
    glEnd();
}