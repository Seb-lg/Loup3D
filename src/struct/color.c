#include "../../inc/struct/color.h"

struct color createColor(float r, float g, float b) {
  struct color tmp;
  tmp.r = r;
  tmp.g = g;
  tmp.b = b;
  return tmp;
}
