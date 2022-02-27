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

    // map[1][1] = 'W';
    // map[1][2] = 'W';
    // map[2][1] = 'W';

    for( int y = 0; y < size; ++y) {
        for(int x = 0; x < size; ++x) {
            if (x == 0 || y == 0 || x == size - 1 || y == size - 1) {
                map[x][y] = 'W';
            } else {
                // map[x][y] = (rand()%10 == 4 ? 'W': ' ');
            }
            printf("%c",map[x][y]);
        }
        printf("\n");
    }

    return map;
}

// float RayCast(float posX, float posY, float angle, char** map, int size) {
//     float rayX = posX;
//     float rayY = posY;

//     float rayCos = cos(angle * (M_PI / 180.0))/10000;
//     float raySin = sin(angle * (M_PI / 180.0))/10000;
    
//     // printf("cos %f sin %f\n", rayCos, raySin);
//     // printf("pos %f pos %f\n", rayX, rayY);
//     while ( rayX >= 0 && rayY >= 0 &&
//             rayX < size && rayY < size &&
//             map[(int)floor(rayX)][(int)floor(rayY)] == ' '){
//         rayX += rayCos;
//         rayY += raySin;
//         // printf("%f %f\n", rayX, rayY);
//     }
//     // exit(0);

//     return sqrt(pow(posX - rayX, 2) + pow(posY - rayY, 2));
// }

float RayCast(float posX, float posY, float angle, char** map, int size) {
    
}