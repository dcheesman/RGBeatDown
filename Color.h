#ifndef Color_h
#define Color_h

#include "Arduino.h"

class Color {
  private:
    int score;

  public:
    int red;
    int green;
    int blue;
    void init();
    void randomize();
    int calculateColorScore(Color c2);
};

#endif
