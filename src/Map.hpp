//
// Created by seub on 3/3/22.
//

#ifndef LOUP3D_MAP_HPP
#define LOUP3D_MAP_HPP


#include <string>
#include <vector>

class Map {
public:
    Map(int size = 50);
    Map(std::string path);

    unsigned char *operator[](unsigned int pos);

public:
    int width;
    int height;
    std::vector<unsigned char> map;
};


#endif //LOUP3D_MAP_HPP
