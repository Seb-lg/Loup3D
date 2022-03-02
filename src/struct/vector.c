#include "../../inc/struct/vector.h"

struct vector2f makeVector2f(float x, float y) {
  struct vector2f tmp;
  tmp.x = x;
  tmp.y = y;
  return tmp;
}

struct vector2i makeVector2i(int x, int y) {
  struct vector2i tmp;
  tmp.x = x;
  tmp.y = y;
  return tmp;
}
