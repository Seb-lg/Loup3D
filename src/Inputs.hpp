//
// Created by seub on 3/3/22.
//

#ifndef LOUP3D_INPUTS_HPP
#define LOUP3D_INPUTS_HPP


#include <iostream>
#include "Graphic.hpp"
#include "Player.hpp"

class Inputs {
public:
    Inputs() = delete;
    Inputs(const std::shared_ptr<Graphic> &window, std::shared_ptr<Player> &player);

    void update(const std::shared_ptr<Graphic> &window, std::shared_ptr<Player> &player);
    void updateCursor(const std::shared_ptr<Graphic> &window, std::shared_ptr<Player> &player);

public:
    float mouseSensitivity;
};


#endif //LOUP3D_INPUTS_HPP
