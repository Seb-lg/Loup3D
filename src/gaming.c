#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "../include/gaming.h"
#include "../include/assert.h"

char** InitMap(int size) {
    srand(time(NULL));
    char** map = malloc(size * sizeof(char*));
    assert(map != NULL);
    for (int i = 0; i < size; ++i) {
        map[i] = malloc(size * sizeof(char));
        assert(map[i] != NULL);
        memset(map[i], ' ', size * sizeof(char));
    }

    map[1][1] = 'W';
    map[1][2] = 'W';
    map[2][1] = 'W';

    for( int y = 0; y < size; ++y) {
        for(int x = 0; x < size; ++x) {
            map[x][y] = (rand()%10 == 4 ? 'W': ' ');
            printf("%c",map[x][y]);
        }
        printf("\n");
    }

    return map;
}

double RayCast(double posX, double posY, double angle, char** map, int size) {
    double rayX = posX;
    double rayY = posY;

    double rayCos = cos(angle);
    double raySin = sin(angle);
    
    while ( rayX >= 0 && rayY >= 0 &&
            rayX < size && rayY < size &&
            map[(int)floor(rayX)][(int)floor(rayY)] == ' '){
        rayX += rayCos;
        rayY += raySin;
    }

    return sqrt(pow(posX - rayX, 2) + pow(posY - rayY, 2));
}