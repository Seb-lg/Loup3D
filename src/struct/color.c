#include "../../include/struct/color.h"

struct color createColor(int r, int g, int b) {
    struct color tmp;
    tmp.r = r;
    tmp.g = g;
    tmp.b = b;
    return tmp;
}