#include <math.h>

#include "../inc/conf.h"
#include "../inc/inputs.h"

float absf(float x) { return x < 0.0f ? -x : x; }
float notZero(float x) { return x == 0.0f ? 1000000000 : x; }

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
  if (xpos > player.mouseX && absf(player.mouseX - xpos) != 0)
    player.angle += notZero(MOUSE_SENSITIVITY * absf(player.mouseX - xpos));
  else if (absf(player.mouseX - xpos) != 0)
    player.angle -= notZero(MOUSE_SENSITIVITY * absf(player.mouseX - xpos));

  if (ypos > player.mouseY && absf(player.mouseY - ypos) != 0)
    player.sightHeight +=
        notZero((MOUSE_SENSITIVITY * 8) * absf(player.mouseY - ypos));
  else if (absf(player.mouseY - ypos) != 0)
    player.sightHeight -=
        notZero((MOUSE_SENSITIVITY * 8) * absf(player.mouseY - ypos));

  player.mouseX = xpos;
  player.mouseY = ypos;
  player.sightHeight = player.sightHeight < -WINDOW_HEIGHT ? -WINDOW_HEIGHT
                       : player.sightHeight > WINDOW_HEIGHT
                           ? WINDOW_HEIGHT
                           : player.sightHeight;
}
