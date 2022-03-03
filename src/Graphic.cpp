//
// Created by seub on 3/3/22.
//

#include "Graphic.hpp"
#include "Helpers/Image.hpp"

Graphic::Graphic() : width(1920), height(1080), fov(90.) {
    if (!glfwInit()) {
        std::cout << ("Initialisation failed: glfw\n") << std::endl;
        exit(0);
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    this->window = glfwCreateWindow(width, height, "Loup3D", NULL, NULL);
    if (!window) {
        std::cout << ("Failed to create window\n") << std::endl;
        exit(0);
    }
    glfwMakeContextCurrent(window);
    glOrtho(0, width, height, 0, 0, 1);

    int a,b;
    textures['W'] = Image::loadBMP("./assets/A.bmp",a,b);

    // OPTI TIME
    this->points.resize(b+1);

//        glfwSetErrorCallback(ErrorCallback);
//        glfwSetWindowSizeCallback(window, ResizeCallback);
}

bool Graphic::update(std::shared_ptr<Player> &player) {
    glfwSwapBuffers(this->window);
    glfwPollEvents();
    glClearColor((float) 135 / 255., (float) 206 / 255., (float) 235 / 255., 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->drawRectangle({0, (float)((this->height / 2) - (int)player->sightHeight)},
                        {(float)this->width, (float)(this->height * 2)},
                        {(float)249 / 255., (float)97 / 255., (float)97 / 255.});
    return glfwWindowShouldClose(this->window);
}

void Graphic::drawVerticalLine(int pos, float lineHeight, std::vector<float> color) {
//    std::cout << pos << " " << lineHeight << " " << this->height / 2 - lineHeight / 2 << " " << this->height / 2 + lineHeight / 2 << std::endl;
    glBegin(GL_LINES);
    glColor3f(color[0], color[1], color[2]);
    glVertex3f(pos, this->height / 2 - lineHeight / 2, 0.0);
    // glVertex3f(00, 200,0.0);
    glColor3f(color[0], color[1], color[2]);
    glVertex3f(pos, this->height / 2 + lineHeight / 2, 0.0);
    // glVertex3f(400, 100,0.0);
    glEnd();
}


void Graphic::drawVerticalLineWithTexture(int pos, int height, std::shared_ptr<Player> &player, unsigned char *img,
                                 int texture_pos, int texture_height) {

    float yPos = (float)this->height / 2 - (float)height / 2 - player->sightHeight;
    float yDelta = (float)height / (float)texture_height;
    img += texture_pos * 3;
    auto elem = points.data();
    for (int i = 0; i < texture_height; i++) {
        elem->x = pos;
        elem->y = yPos;
        yPos += yDelta;
        elem->r = img[0];
        elem->g = img[1];
        elem->b = img[2];
        elem += 1;
        img += texture_height * 3;
    }

    glColor3ub(255, 255, 255);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(2, GL_FLOAT, sizeof(struct Point), &points[0].x);
    glColorPointer(3, GL_UNSIGNED_BYTE, sizeof(struct Point), &points[0].r);
    // glLineWidth( 3.0 );
    // glPointSize(3.0);
    glDrawArrays(GL_LINE_STRIP, 0, texture_height);
//    free(points);
}

void Graphic::drawRectangle(std::vector<float> pos, std::vector<float> size,
                   std::vector<float> color) {
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_QUADS);
    glVertex3f(pos[0], pos[1], 0);
    glVertex3f(pos[0] + size[0], pos[1], 0);
    glVertex3f(pos[0] + size[0], pos[1] + size[1], 0);
    glVertex3f(pos[0], pos[1] + size[1], 0);
    glEnd();
}
