#ifndef __MY__VECTOR__
#define __MY__VECTOR__

struct vector2f {
    float x;
    float y;
};

struct vector2i {
    int x;
    int y;
};


struct vector2f makeVector2f(float x, float y);
struct vector2i makeVector2i(int x, int y);

#endif