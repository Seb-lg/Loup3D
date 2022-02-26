#include "../include/inputs.h"
#include "../include/conf.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (key == GLFW_KEY_S && action == GLFW_PRESS)
        angle -= 0.1;
    if (key == GLFW_KEY_D )
        angle += 0.1;
}