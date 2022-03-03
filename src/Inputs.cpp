//
// Created by seub on 3/3/22.
//

#include <cmath>
#include "Inputs.hpp"

Inputs::Inputs(const std::shared_ptr<Graphic> &window, std::shared_ptr<Player> &player):mouseSensitivity(.5f) {
    glfwSetKeyCallback(window->window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
        if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
            glfwSetWindowShouldClose(window, GLFW_TRUE);
    });

    glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_TRUE);
    glfwSetInputMode(window->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    double a,b;
    glfwGetCursorPos(window->window, &a,&b);
    player->mouseX = a;
    player->mouseY = b;
}

void Inputs::update(const std::shared_ptr<Graphic> &window, std::shared_ptr<Player> &player) {
    if (glfwGetKey(window->window, GLFW_KEY_W) == GLFW_PRESS) {
        player->posX += cosf(player->angle * (M_PIf / 180.f)) / 10.f;
        player->posY += sinf(player->angle * (M_PIf / 180.f)) / 10.f;
    }
    if (glfwGetKey(window->window, GLFW_KEY_S) == GLFW_PRESS) {
        player->posX -= cosf(player->angle * (M_PIf / 180.f)) / 10.f;
        player->posY -= sinf(player->angle * (M_PIf / 180.f)) / 10.f;
    }
    if (glfwGetKey(window->window, GLFW_KEY_A) == GLFW_PRESS) {
        player->posX -= cosf((player->angle + 90.f) * (M_PIf / 180.f)) / 10.f;
        player->posY -= sinf((player->angle + 90.f) * (M_PIf / 180.f)) / 10.f;
    }
    if (glfwGetKey(window->window, GLFW_KEY_D) == GLFW_PRESS) {
        player->posX -= cosf((player->angle - 90.f) * (M_PIf / 180.f)) / 10.f;
        player->posY -= sinf((player->angle - 90.f) * (M_PIf / 180.f)) / 10.f;
    }
    //TODO: replace the mapsize with the actual size of the map
    int MapSize = 100;
    player->posX = player->posX < 0 ? 0
                                    : player->posX > MapSize ? MapSize
                                                             : player->posX;
    player->posY = player->posY < 0 ? 0
                                    : player->posY > MapSize ? MapSize
                                                             : player->posY;
    this->updateCursor(window, player);
}

void Inputs::updateCursor(const std::shared_ptr<Graphic> &window, std::shared_ptr<Player> &player) {
    double xpos, ypos;
    glfwGetCursorPos(window->window, &xpos, &ypos);

    if (xpos > player->mouseX && fabs(player->mouseX - xpos) != 0) {
        player->angle += this->mouseSensitivity * fabs(player->mouseX - xpos);
    }
    else if (fabs(player->mouseX - xpos) != 0) {
        player->angle -= this->mouseSensitivity * fabs(player->mouseX - xpos);
    }

    if (ypos > player->mouseY && fabs(player->mouseY - ypos) != 0) {
        player->sightHeight +=
                (this->mouseSensitivity * 8) * fabs(player->mouseY - ypos);
    }
    else if (fabs(player->mouseY - ypos) != 0) {
        player->sightHeight -=
                (this->mouseSensitivity * 8) * fabs(player->mouseY - ypos);
    }

    player->mouseX = xpos;
    player->mouseY = ypos;
    player->sightHeight = player->sightHeight < -window->height ? -window->height
                                                                : player->sightHeight > window->height
                                                                  ? window->height
                                                                  : player->sightHeight;
}