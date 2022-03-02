#include <math.h>

#include "../inc/conf.h"
#include "../inc/inputs.h"

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
