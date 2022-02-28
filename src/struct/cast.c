#include "../../include/struct/cast.h"

struct cast makeCast(float distance, char type) {
    struct cast tmp;
    tmp.distance = distance;
    tmp.type = type;
    return tmp;
}