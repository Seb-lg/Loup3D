#include <math.h>

#include "../include/inputs.h"
#include "../include/conf.h"

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if (key == GLFW_KEY_A )
        player.angle -= 1;
    if (key == GLFW_KEY_D )
        player.angle += 1;
    if (key == GLFW_KEY_W) {
        player.posX += cos(player.angle * (M_PI / 180.0))/10;
        player.posY += sin(player.angle * (M_PI / 180.0))/10;
        player.posX = player.posX < 0 ? 0 : player.posX > 50 ? 50 : player.posX;
        player.posY = player.posY < 0 ? 0 : player.posY > 50 ? 50 : player.posY;
    }
        
}