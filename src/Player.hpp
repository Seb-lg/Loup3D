//
// Created by seub on 3/3/22.
//

#ifndef LOUP3D_PLAYER_HPP
#define LOUP3D_PLAYER_HPP


class Player {
public:
    Player();
public:
    float posX;
    float posY;

    float angle;
    float sightHeight;

    // Private members used only for function memory
    float mouseX;
    float mouseY;
};


#endif //LOUP3D_PLAYER_HPP
