#include <math.h>
#include <string.h>
#include <time.h>

#include "./inc/conf.h"
#include "./inc/game_engine.h"
#include "./inc/graphics.h"
#include "./inc/inputs.h"
#include "./inc/struct/player.h"
#include "./inc/utils.h"

struct player player;

void gameUpdate(GLFWwindow *window, char **map, size_t mapHeight) {
  int nbFrame = 0;
  int width, height;
  unsigned char *img = load_bmp("./assets/A.bmp", &width, &height);

  struct timespec tstart = {0, 0}, tend = {0, 0};
  clock_gettime(CLOCK_MONOTONIC, &tstart);
  while (!glfwWindowShouldClose(window)) {
    glClearColor((float)135 / 255., (float)206 / 255., (float)235 / 255., 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    DrawRectangle(
        makeVector2i(0, Height / 2.0), makeVector2i(Width, Height / 2.0),
        createColor((float)249 / 255., (float)97 / 255., (float)97 / 255.));

    for (int i = 0; i < Width; ++i) {
      float angleForCast =
          player.angle - (FOV / 2) + ((FOV / (float)Width) * (float)i);
      // TODO: The 100 value here is arbitrary, it stops the raycasting after
      // this value is a wall is not hitten before, we should find a values
      // which makes sense
      struct cast value =
          RayCast(player.posX, player.posY, angleForCast, map, 100);
      if (value.distance == -1.0)
        continue;
      value.distance =
          value.distance * cos((player.angle - angleForCast) * (M_PI / 180.0));
      value.distance = Height / value.distance;

      float color = (float)(value.type - 65) / 25;
      DrawVerticalLine(i, value.distance,
                       createColor(color, color, value.hitpoint));
    }
    nbFrame++;

    glfwPollEvents();
    HandleInput(window);

    glfwSwapBuffers(window);
    clock_gettime(CLOCK_MONOTONIC, &tend);
    if (((double)tend.tv_sec + 1.0e-9 * tend.tv_nsec) -
            ((double)tstart.tv_sec + 1.0e-9 * tstart.tv_nsec) >
        0.5) {
      printf("fps: %4d\n", nbFrame * 2);
      nbFrame = 0;
      clock_gettime(CLOCK_MONOTONIC, &tstart);
    } else {
      // 	printf("le delta %f\n", ((double)tend.tv_sec
      // + 1.0e-9*tend.tv_nsec) -
      //    ((double)tstart.tv_sec + 1.0e-9*tstart.tv_nsec));
    }
  }
  freeMap(map, mapHeight);
}

void startGame(char **map, size_t mapHeight) {
  // Init GLFW Window
  GLFWwindow *window = InitGraphics();
  player = InitPlayer();
  player.angle = 90.;
  player.posX = 2;
  player.posY = 2;
  // Init keyboard input
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPosCallback(window, cursor_position_callback);
  // Change display to orthogonal --> closer to a framebuffer
  glOrtho(0, Width, Height, 0, 0, 1);

  // Start main loop
  gameUpdate(window, map, mapHeight);
}

int main(int ac, char **av) {
  size_t mapWidth = 0;
  size_t mapHeight = 0;
  char **map = NULL;
  if (ac == 2) {
    map = LoadMapFromFile(av[1], &mapWidth, &mapHeight);
    assert(mapWidth != 0);
    assert(mapHeight != 0);
  } else {
    map = CreateRandomMap(100, time(NULL));
  }
  assert(map != NULL);
  // printMap(map, mapHeight);

  startGame(map, mapHeight);
  return 0;
}
