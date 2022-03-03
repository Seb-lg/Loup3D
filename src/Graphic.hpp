//
// Created by seub on 3/3/22.
//

#ifndef LOUP3D_GRAPHIC_HPP
#define LOUP3D_GRAPHIC_HPP


#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include "Player.hpp"

class Graphic {
public:
    Graphic();

    static std::shared_ptr<Graphic> get() {static std::shared_ptr<Graphic> graphic = std::make_shared<Graphic>();return graphic;}
    bool update(std::shared_ptr<Player> &player);

    void drawVerticalLine(int pos, float lineHeight, std::vector<float> color);
    void drawVerticalLineWithTexture(int pos, int height, std::shared_ptr<Player> &player, unsigned char *img,
                                     int texture_pos, int texture_height);
    void drawRectangle(std::vector<float> pos, std::vector<float> size,
                       std::vector<float> color);

public:
    int width;
    int height;
    float fov;
    GLFWwindow *window;
    std::map<unsigned char, std::vector<unsigned char>> textures;

private:
    struct Point {
        float x, y;
        unsigned char r, g, b;
    };
    std::vector<Point> points;
};


#endif //LOUP3D_GRAPHIC_HPP
