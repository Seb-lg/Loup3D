//
// Created by seub on 3/3/22.
//

#ifndef LOUP3D_RAYCASTING_HPP
#define LOUP3D_RAYCASTING_HPP

#include <memory>
#include "Graphic.hpp"
#include "Player.hpp"
#include "Map.hpp"

class Raycasting {
public:
    struct cast{
        float distance;
        unsigned char type;

        float hitpoint;
    };
    typedef struct cast cast;
public:
    cast static     getHeight(std::shared_ptr<Player> &player, float angle, std::shared_ptr<Map> &map);
    void static     drawMap(std::shared_ptr<Graphic> &window, std::shared_ptr<Player> &player, std::shared_ptr<Map> &map);
};


#endif //LOUP3D_RAYCASTING_HPP
