 #include "CountDown.h"

void CountDown::init (int counterLength) {
  lengthMillis = counterLength;
}

void CountDown::start() {
  endtime = millis() + lengthMillis;
}

int CountDown::seconds () {
  return floor((endtime - millis())/1000); // Millis to seconds
}

boolean CountDown::isDone () {
  if (endtime - millis() > 0 ) {
    return false;
  }
  return true;
}
