#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "../include/struct/vector.h"
#include "../include/gaming.h"
#include "../include/assert.h"

#define ABS(a) (a < 0 ? -a : a)
#define SIGN(a,b) (a < 0 && b > 0 ? -a : a > 0 && b < 0 ? -a : a)

char** InitMap(int size) {
    srand(time(NULL));
    char** map = malloc(size * sizeof(char*));
    assert(map != NULL);
    for (int i = 0; i < size; ++i) {
        map[i] = malloc(size * sizeof(char));
        assert(map[i] != NULL);
        memset(map[i], ' ', size * sizeof(char));
    }

    // map[10][10] = 'W';
    // map[11][12] = 'W';
    // map[12][11] = 'W';

    for( int y = 0; y < size; ++y) {
        for(int x = 0; x < size; ++x) {
            if (x == 0 || y == 0 || x == size - 1 || y == size - 1) {
                map[x][y] = 'W';
            } else {
               map[x][y] = (rand()%15 == 4 ? 'W': ' ');
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


struct cast RayCast(float posX, float posY, float angle, char** map, int size) {
    angle = angle < 0 ? angle + 360.0 : angle > 360.0 ? angle - 360.0: angle;
    struct vector2f rayPos = makeVector2f(posX, posY);
    struct vector2f vRayDir = makeVector2f(cos(angle * (M_PI / 180.0)), sin(angle * (M_PI / 180.0)));
            
    // Lodev.org also explains this additional optimistaion (but it's beyond scope of video)
    // struct vector2f vRayUnitStepSize = { abs(1.0f / vRayDir.x), abs(1.0f / vRayDir.y) };

    struct vector2i vStep;
    float editMinimal = 0.001;

    // Establish Starting Conditions
    vStep.x = cos(angle * (M_PI / 180.0)) < 0 ? -1 : 1;
    vStep.y = sin(angle * (M_PI / 180.0)) < 0 ? -1 : 1;
    // printf("\n\n");
    // printf("direction x:%d y:%d\n", vStep.x, vStep.y);

    // Perform "Walk" until collision or range check
    int bTileFound = 0;
    float fDistance = 0.0f;
    struct vector2f rayHypot = makeVector2f(0,0);
    struct vector2f rayAdd = makeVector2f(0,0);
    int i = 100;
    while (!bTileFound && --i > 0)
    {
        if (vStep.x == 1) { // CAH
            rayAdd.x = (1.0 - (rayPos.x - (float)floor(rayPos.x)));
            rayHypot.x =  rayAdd.x / cos(angle * (M_PI / 180.0));
        } else {
            rayAdd.x = ((rayPos.x - (float)floor(rayPos.x)));
            rayHypot.x = rayAdd.x / cos(angle * (M_PI / 180.0));
        }

        if (vStep.y == 1) { // SOH
            rayAdd.y = (1.0 - (rayPos.y - (float)floor(rayPos.y)));
            rayHypot.y = rayAdd.y / sin(angle * (M_PI / 180.0));
        } else {
            rayAdd.y = ((rayPos.y - (float)floor(rayPos.y)));
            rayHypot.y = rayAdd.y / sin(angle * (M_PI / 180.0));
        }

        // printf("--------------------------\nangle\t%f\nsteps\t%f %f\nrayPos\t%f %f\nrayHypo\t%f %f\n", angle, rayAdd.x, rayAdd.y, rayPos.x, rayPos.y, rayHypot.x, rayHypot.y);

        if (ABS(rayHypot.x) < ABS(rayHypot.y)) {
            rayPos.x += SIGN(rayAdd.x, vStep.x) + editMinimal * vStep.x;
            rayPos.y += SIGN(sin(angle * (M_PI / 180.0)) * rayHypot.x, vStep.y);
            // rayPos.y += SIGN(cos(angle * (M_PI / 180.0)) * rayHypot.x, vStep.y);
            // printf("use cos\n %d %f\n", vStep.y, SIGN(sin(angle * (M_PI / 180.0)) * rayHypot.x, vStep.y));
        } else {
            // printf("wtf %f %f\n", rayPos.y, SIGN(rayAdd.y,vStep.y) + editMinimal * vStep.y);
            rayPos.y += SIGN(rayAdd.y,vStep.y) + editMinimal * vStep.y;
            // printf("wtf %f\n", rayPos.y);
            rayPos.x += SIGN(cos(angle * (M_PI / 180.0)) * rayHypot.y, vStep.x);
            // rayPos.x += SIGN(sin(angle * (M_PI / 180.0)) * rayHypot.y, vStep.x);
            // printf("use sin\n %d %f\n", vStep.x, SIGN(cos(angle * (M_PI / 180.0)) * rayHypot.y, vStep.x));
        }

        // Test tile at new test point
        if (rayPos.x >= 0 && rayPos.x < size && rayPos.y >= 0 && rayPos.y < size)
        {
            if (map[(int)rayPos.x][(int)rayPos.y] != ' ')
            {
                bTileFound = 1;
            }
        } else {
            return makeCast(-1, ' ');
        }
        struct timespec sleep = {1,0};
        // nanosleep(&sleep,&sleep);
    }
    // exit(0);
    // printf("--------------------------\n%f\n",sqrt(((rayPos.x-posX)*(rayPos.x-posX))+((rayPos.y-posY)*(rayPos.y-posY))));
    return makeCast(sqrt(((rayPos.x-posX)*(rayPos.x-posX))+((rayPos.y-posY)*(rayPos.y-posY))), map[(int)rayPos.x][(int)rayPos.y]);



    // float rayX = posX;
    // float rayY = posY;

    // float angleX = cos(angle * (M_PI / 180.0));
    // float angleY = sin(angle * (M_PI / 180.0));

    // float distX;
    // float distY;

    // struct vector2f pos;

    // while ( rayX >= 0 && rayY >= 0 && rayX < size && rayY < size &&map[(int)floor(rayX)][(int)floor(rayY)] == ' ') {

    //     distX = angleX > 0 ? rayX - floor(rayX) : rayX - floor(rayX + 1);
    //     distY = angleY > 0 ? rayY - floor(rayY) : rayY - floor(rayY + 1);
        
    //     distX = distX == 0 ? 0.001: distX;

    //     printf("%f %f\n", distX, angleX);
    //     distX = distX * angleX;
    //     distY = distY * angleY;

    //     // if (distX < distY) {
    //         rayX += distX;
    //         // rayY += distX / angleY;
    //     // } else {
    //         // rayX += distY / angleX;
    //         // rayY += distY;
    //     // }
    //     // printf("%f %f\n", rayX, rayY);

    // }
    // return sqrt(pow(posX - rayX, 2) + pow(posY - rayY, 2));
}