#include <math.h>

#include "./include/struct/player.h"
#include "./include/graphics.h"
#include "./include/gaming.h"
#include "./include/inputs.h"
#include "./include/conf.h"

struct player player;

void gameUpdate(GLFWwindow* window) {
	char** map = InitMap(50);
	// float angle = 0.0;

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0,0,0,0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// glLineWidth(100);

		for (int i = 0; i < Width; ++i) {
			// printf("cast %f %f\n", posX, posY);
			float angleForCast = player.angle - 45.0  + ((90.0 / (float)Width)*(float)i);
			float valueH = Height / RayCast(player.posX, player.posY, angleForCast, map, 50);
			valueH = valueH * cos(angleForCast * (M_PI / 180.0));
			DrawVerticalLine(i, valueH, createColor(1,0,0));
		}

		glfwSwapBuffers(window);
		// angle += 0.1;
		glfwPollEvents();
		printf("Angle: %f Pos: %f %f\r", player.angle, player.posX, player.posY);
	}
}


int main(int ac, char** av) {
	//Init GLFW Window
	GLFWwindow* window = InitGraphics(ac, av);
	player = InitPlayer();
	//Init keyboard input
	glfwSetKeyCallback(window, key_callback);
	glOrtho(0, Width, Height, 0, 0, 1);

	//Start main loop
	gameUpdate(window);
}