#include "../include/graphics.h"
#include "../include/conf.h"
#include <assert.h>
#include <math.h>
#include <string.h>

void ErrorCallback(int code, const char *message) {
  printf("Code: %d, Message: %s\n", code, message);
  exit(42);
}

GLFWwindow *InitGraphics() {
  if (!glfwInit()) {
    printf("Initialisation failed: glfw\n");
    exit(0);
  }

  glfwSetErrorCallback(ErrorCallback);

  GLFWwindow *window = glfwCreateWindow(Width, Height, "Loup3D", NULL, NULL);
  if (!window) {
    printf("Failed to create window\n");
    exit(0);
  }
  glfwMakeContextCurrent(window);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  return window;
}

void DrawVerticalLine(int pos, int height, struct color color) {
  glBegin(GL_LINES);
  glColor3f(color.r, color.g, color.b);
  glVertex3f(pos, Height / 2 - height / 2, 0.0);
  // glVertex3f(00, 200,0.0);
  glColor3f(color.r, color.g, color.b);
  glVertex3f(pos, Height / 2 + height / 2, 0.0);
  // glVertex3f(400, 100,0.0);
  glEnd();
}

void DrawVerticalLineWithTexture(int pos, int height, struct color color, int texture_pos, int texture_height) {
  glBegin(GL_LINES);
  glColor3f(color.r, color.g, color.b);
  glVertex3f(pos, Height / 2 - height / 2, 0.0);
  // glVertex3f(00, 200,0.0);
  glColor3f(color.r, color.g, color.b);
  glVertex3f(pos, Height / 2 + height / 2, 0.0);
  // glVertex3f(400, 100,0.0);
  glEnd();
}

void DrawRectangle(struct vector2i pos, struct vector2i size,
                   struct color color) {
  glColor3f(color.r, color.g, color.b);
  glBegin(GL_QUADS);
  glVertex3f(pos.x, pos.y, 0);
  glVertex3f(pos.x + size.x, pos.y, 0);
  glVertex3f(pos.x + size.x, pos.y + size.y, 0);
  glVertex3f(pos.x, pos.y + size.y, 0);
  glEnd();
}

unsigned char *load_bmp(char *path, int *width, int *height) {
  printf("Reading image %s\n", path);
  *width = -1;
  *height = -1;
  // Data read from the header of the BMP file
  unsigned char header[54];
  unsigned int dataPos;
  unsigned int imageSize;
  // Actual RGB data
  unsigned char *data;

  // Open the file
  FILE *file = fopen(path, "rb");
  if (!file) {
    printf("Image could not be opened\n");
    return NULL;
  }

  // Read the header, i.e. the 54 first bytes

  // If less than 54 byes are read, problem
  if (fread(header, 1, 54, file) != 54) {
    printf("Not a correct BMP file\n");
    return NULL;
  }
  // A BMP files always begins with "BM"
  if (header[0] != 'B' || header[1] != 'M') {
    printf("Not a correct BMP file\n");
    return NULL;
  }
  // Make sure this is a 24bpp file
  if (*(int *)&(header[0x1E]) != 0) {
    printf("Not a correct BMP file\n");
    return NULL;
  }
  if (*(int *)&(header[0x1C]) != 24) {
    printf("Not a correct BMP file\n");
    return NULL;
  }

  // Read the information about the image
  dataPos = *(int *)&(header[0x0A]);
  imageSize = *(int *)&(header[0x22]);
  *width = *(int *)&(header[0x12]);
  *height = *(int *)&(header[0x16]);

  // Some BMP files are misformatted, guess missing information
  if (imageSize == 0)
    imageSize = width[0] * height[0] *
                3; // 3 : one byte for each Red, Green and Blue component
  if (dataPos == 0)
    dataPos = 54; // The BMP header is done that way

  // Create a buffer
  data = (unsigned char *)malloc(imageSize);

  // Read the actual data from the file into the buffer
  fread(data, 1, imageSize, file);

  // Everything is in memory now, the file wan be closed
  fclose(file);

  if (0) {
    // swap y-axis
    unsigned char *tmpBuffer = (unsigned char *)malloc(width[0] * 3);
    int size = width[0] * 3;
    for (int i = 0; i < height[0] / 2; i++) {
      // copy row i to tmp
      memcpy(tmpBuffer, data + width[0] * 3 * i, size);
      // copy row h-i-1 to i
      memcpy(data + width[0] * 3 * i, data + width[0] * 3 * (height[0] - i - 1),
             size);
      // copy tmp to row h-i-1
      memcpy(data + width[0] * 3 * (height[0] - i - 1), tmpBuffer, size);
    }
    free(tmpBuffer);
  }

  return data;
}
