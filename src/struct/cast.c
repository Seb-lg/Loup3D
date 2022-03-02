#include "../../include/struct/cast.h"

struct cast makeCast(float distance, char type, float hitpoint) {
  struct cast tmp;
  tmp.distance = distance;
  tmp.type = type;
  tmp.hitpoint = hitpoint;
  return tmp;
}
