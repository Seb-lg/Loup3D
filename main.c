#include "./include/graphics.h"
#include "./include/gaming.h"
#include "./include/inputs.h"
#include "./include/conf.h"

double angle = 0.0;

void gameUpdate(GLFWwindow* window) {
	char** map = InitMap(50);
	int posX = 10;
	int posY = 10;
	// double angle = 0.0;

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0,0,0,0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// glLineWidth(100);

		for (int i = 0; i < Width; ++i) {
			double valueH = Height / RayCast(posX, posY, angle + ((90.0 / (double)Width)*(double)i) , map, 50);
			DrawVerticalLine(i, valueH, createColor(1,0,0));
		}

		glfwSwapBuffers(window);
		// angle += 0.01;
		glfwPollEvents();
		printf("Angle: %f %f\r", angle, glfwGetTime());
	}
}


int main(int ac, char** av) {
	//Init GLFW Window
	GLFWwindow* window = InitGraphics(ac, av);
	//Init keyboard input
	glfwSetKeyCallback(window, key_callback);
	glOrtho(0, Width, Height, 0, 0, 1);

	//Start main loop
	gameUpdate(window);
}