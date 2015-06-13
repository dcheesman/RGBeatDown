#include <LiquidCrystal.h>

const int PREGAME = 0;
const int RUNGAME = 1;
const int RESULTS = 2;

int gameState;

int preGameMillis = 15000;
int gameMillis = 20000;



Player p1;
Player p2;
CountDown preGameCountDown;
CountDown gameCountDown;
Color roundColor;


void setup() {
    roundColor = new Color();
    lcd.begin(16, 2);
    lcd.print("RGBeat Down");
    lcd.setCursor(0, 1);
    lcd.print("Get Ready!");
    delay(2000);
    reset();
}

void loop() {
  switch (gameState) {
    case PREGAME:
      preGame();
      break;
    case RUNGAME:
      runGame();
      break;
    case RESULTS:
      results()
      break;
    default:
      //something went wrong if you're here
  }
}

void reset() {
    p1 = new Player();
    p2 = new Player();

    gameCountDown = new CountDown(gameMillis);
    preGameCountDown = new CountDown(preGameMillis);

    preGameCountDown.start()
    gameState = PREGAME;

    roundColor.randomize();
}

void preGame () {
   lcd.setCursor(0,0);
   lcd.print("Staring in");
   lcd.setCursor(0,1);
   lcd.print(preGameCountDown.seconds());
   if(preGameCountDown.isDone()){
     gameCountDown.start();
     gameState = RUNGAME;
   }
}

void runGame () {
   lcd.setCursor(0,0);
   lcd.print("Match Colors");
   lcd.setCursor(0,1);
   lcd.print(gameCountDown.seconds());

   if(gameCountDown.isDone() || (p1.locked && p2.locked)){
      if(!p1.locked) {
        p1.lockInGuess();
      }
      if(!p2.locked) {
        p2.lockInGuess();
      }

      p1.score = roundColor.calculateColorScore(p1);
      p1.score = roundColor.calculateColorScore(p1);

      gameState = RESULTS;
   }
}

void results () {
   lcd.setCursor(0,0);
   lcd.print("Game Over");
   delay(2000);

   lcd.setCursor(0,0);
   lcd.print("P1: " + p1.score);
   lcd.setCursor(0,1);
   lcd.print("P2: " + p2.score);
   delay(2000);



   reset();
}
