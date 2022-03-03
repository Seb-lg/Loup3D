#ifndef __MY_PLAYER__
#define __MY_PLAYER__

struct player {
  float posX;
  float posY;

  float angle;
  float sightHeight;

  // Private members used only for function memory
  float mouseX;
  float mouseY;
};

struct player InitPlayer();

#endif
