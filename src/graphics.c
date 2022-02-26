#include "../include/graphics.h"
#include "../include/conf.h"

void ErrorCallback(int code, const char* message) {
    printf("Code: %d, Message: %s\n", code, message);
    exit(42);
}

GLFWwindow* InitGraphics(int ac, char **av){
    if (!glfwInit()){
        printf("Initialisation failed: glfw\n");
        exit(0);
    }

    glfwSetErrorCallback(ErrorCallback);

    GLFWwindow* window = glfwCreateWindow(Width, Height, "Loup3D", NULL, NULL);
    if (!window)
    {
        printf("Failed to create window\n");
        exit(0);
    }
    glfwMakeContextCurrent(window);
    return window;
}

void DrawVerticalLine(int pos, int height, struct color color) {
    glBegin(GL_LINES);
		glColor3f(color.r,color.g,color.b);
        glVertex3f(pos,Height/2 - height/2,0.0);
        // glVertex3f(00, 200,0.0);
		glColor3f(color.r,color.g,color.b);
        glVertex3f(pos,Height/2 + height/2,0.0);
        // glVertex3f(400, 100,0.0);
    glEnd();
}