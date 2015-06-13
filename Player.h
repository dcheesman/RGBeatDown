#ifndef Player_h
#define Player_h

#include "Arduino.h"
#include "Color.h"

class Player {
  private:
    const int RED = 0;
    const int GREEN = 1;
    const int BLUE = 2;
    
  public:
    Color* color;
    boolean locked;
    int locktime;
    int colorMode;
    int score;
    void init();
    void reset();
    void nextMode();
    void lockInGuess();

};

#endif
