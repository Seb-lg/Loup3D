//
// Created by seub on 3/3/22.
//

#include "Map.hpp"
#include "Helpers/PerlinNoise.hpp"

#include <iostream>

Map::Map(int size):width(size), height(size), map(size * size) {
    const siv::PerlinNoise::seed_type seed = 19837u;
    const siv::PerlinNoise perlin{ seed };

    for (int y = 0; y < size; ++y)
    {
        for (int x = 0; x < size; ++x)
        {
            map[x + y * width] = (255. * perlin.octave2D_01((x * 0.01), (y * 0.01), 4)) > 210. ? 'W': ' ';
            if (x == 0 || y == 0 || y == size - 1 || x == size - 1)
                map[x + y * width] = 'W';
            std::cout << map[x + y * width];
        }
        std::cout << std::endl;
    }

    //TODO: edit the perlin noise to create walls based on the average value of the map
    //  Walls should cover 20% of the map
}

Map::Map(std::string path) {

}

unsigned char* Map::operator[](unsigned int pos) {
    return map.data() + pos * this->width;
}
