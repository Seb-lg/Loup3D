#include <math.h>

#include "../include/inputs.h"
#include "../include/conf.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    float sensitivity = 2;
    if (xpos > player.mouseX)
        player.angle += sensitivity;
    else
        player.angle -= sensitivity;

    player.mouseX = xpos;
    player.mouseY = ypos;
}
