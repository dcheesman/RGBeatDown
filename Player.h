#ifndef Player_h
#define Player_h

#include "Arduino.h"
#include "Color.h"

class Player {
  private:

    
  public:
    static const int RED = 0;
    static const int GREEN = 1;
    static const int BLUE = 2;
    Color* color;
    boolean locked;
    boolean isIncrement;
    int startPosition;
    int locktime;
    int colorMode;
    int score;
    void init();
    void reset();
    void nextMode();
    void colorChange(int delta);
    void lockInGuess();
    int currentPosition();

};

#endif
