#include <math.h>

#include "./include/struct/player.h"
#include "./include/graphics.h"
#include "./include/gaming.h"
#include "./include/inputs.h"
#include "./include/conf.h"

struct player player;

void gameUpdate(GLFWwindow* window) {
	int mapSize = 100;
	float fov = 60.;
	char** map = InitMap(mapSize);


	// float angle = 0.0;
	RayCast(22.1517525, 33.0306244, 270.0, map, mapSize);
	// exit(0);
	printf("--------------------------------------------------------\n");
	RayCast(player.posX, player.posY, 0., map, mapSize);
	printf("--------------------------------------------------------\n");
	RayCast(player.posX, player.posY, 90., map, mapSize);
	printf("--------------------------------------------------------\n");
	RayCast(player.posX, player.posY, 270., map, mapSize);
	printf("--------------------------------------------------------\n");
	RayCast(player.posX, player.posY, 360., map, mapSize);


	while (!glfwWindowShouldClose(window)) {
		glClearColor(1,1,1,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// glLineWidth(100);
		// exit(42);

		for (int i = 0; i < Width; ++i) {
			// printf("cast %f %f\n", posX, posY);
			float angleForCast = player.angle - (fov / 2)  + ((fov / (float)Width)*(float)i);
			struct cast value = RayCast(player.posX, player.posY, angleForCast, map, mapSize);
			// float valueH = RayCast(player.posX, player.posY, player.angle, map, mapSize);
			if (value.distance == -1.0)
				continue;
			value.distance = value.distance * cos((player.angle - angleForCast) * (M_PI / 180.0));
			value.distance = Height / value.distance;
			// printf("wall height:%f\n", value.distance);
			// printf("%f\n", player.angle - angleForCast);

			// printf("value.distance:%f\n", angleForCast);
			printf("(float)(value.type)/255.f=%f\n", (float)(value.type)/255.f);
			DrawVerticalLine(i, value.distance, createColor(1,0,0));
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
	player.angle = 90.;
	player.posX = 2;
	player.posY = 2;
	//Init keyboard input
	glfwSetKeyCallback(window, key_callback);
	glOrtho(0, Width, Height, 0, 0, 1);

	//Start main loop
	gameUpdate(window);
}