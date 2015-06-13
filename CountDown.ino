class CountDown {
  int endtime;
  int lengthMillis;
  CountDown (int counterLength) {
    lengthMillis = counterLength;
  }
  
  void start() {
    endtime = millis() + lengthMillis;
  }
  
  int seconds () {
    return floor((endtime - millis())/1000); // Millis to seconds 
  }

  boolean isDone () {
    if (endtime - millis() > 0 ) {
      return false;
    }  
    return true;
  }
   
}
