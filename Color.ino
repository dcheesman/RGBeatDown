class Color{
  int red;
  int green;
  int blue;
  
  Color () {
    red = 0;
    green = 0;
    blue = 0;
  }
  
  void randomize() {
    red = floor(random(255));
    green = floor(random(255));
    blue = floor(random(255));
  }
  
  int calculateColorScore(Color c2) {
    int score = 0;
    score += abs(c2.red - red);
    score += abs(c2.green - green);
    score += abs(c2.blue - blue);
    
    return score;
  }
}
