#include <math.h>

#include "../inc/conf.h"
#include "../inc/inputs.h"

void HandleInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
    player.posX += cos(player.angle * (M_PI / 180.0)) / 10;
    player.posY += sin(player.angle * (M_PI / 180.0)) / 10;
  }
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
    player.posX -= cos(player.angle * (M_PI / 180.0)) / 10;
    player.posY -= sin(player.angle * (M_PI / 180.0)) / 10;
  }
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
    player.posX -= cos((player.angle + 90.) * (M_PI / 180.0)) / 10;
    player.posY -= sin((player.angle + 90.) * (M_PI / 180.0)) / 10;
  }
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
    player.posX -= cos((player.angle - 90.) * (M_PI / 180.0)) / 10;
    player.posY -= sin((player.angle - 90.) * (M_PI / 180.0)) / 10;
  }
  player.posX = player.posX < 0         ? 0
                : player.posX > MapSize ? MapSize
                                        : player.posX;
  player.posY = player.posY < 0         ? 0
                : player.posY > MapSize ? MapSize
                                        : player.posY;
}

void key_callback(GLFWwindow *window, int key, int scancode, int action,
                  int mods) {
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
  if (xpos > player.mouseX)
    player.angle += MOUSE_SENSITIVITY;
  else
    player.angle -= MOUSE_SENSITIVITY;
  player.mouseX = xpos;
  player.mouseY = ypos;
}
