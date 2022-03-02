#ifndef __MY_CAST__
#define __MY_CAST__

struct cast {
  float distance;
  char type;

  float hitpoint;
};

struct cast makeCast(float distance, char type, float hitpoint);

#endif
