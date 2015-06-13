#ifndef CountDown_h
#define CountDown_h

#include "Arduino.h"

class CountDown {
  private:
    int endtime;
    int lengthMillis;

  public:
    void init(int counterLength);
    void start();
    int seconds();
    boolean isDone();
};

#endif
