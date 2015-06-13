class Player () {
  int red, green, blue;
  Color color;
  int locktime;
  String colorMode;
  boolean locked;
  
  int score;
  
  Player () {
    reset();
    color = new Color();
    score = 0;
  }
  
  void reset() {
    mode = "red"

    color.red = 0;
    color.green = 0;  
    color.blue = 0
    locked = false;
  }
  
  void lockInGuess () {
    locked = true;
    locktime = millis();
  }
}
