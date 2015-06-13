#include <LiquidCrystal.h>
#include "Color.h"
#include "Player.h"
#include "CountDown.h"

// TODO: initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int PREGAME = 0;
const int RUNGAME = 1;
const int RESULTS = 2;

int gameState;

int preGameMillis = 15000;
int gameMillis = 20000;


Color* roundColor;
Player* p1;
Player* p2;
CountDown* preGameCountDown;
CountDown* gameCountDown;



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
      results();
      break;
    default:
      //something went wrong if you're here
      break;
  }
}

void reset() {
    p1 = new Player();
    p2 = new Player();

    gameCountDown = new CountDown();
    gameCountDown->init(gameMillis);
    preGameCountDown = new CountDown();
    preGameCountDown->init(preGameMillis);
    preGameCountDown->start();
    gameState = PREGAME;

    roundColor->randomize();
}

void preGame () {
   lcd.setCursor(0,0);
   lcd.print("Staring in");
   lcd.setCursor(0,1);
   lcd.print(preGameCountDown->seconds());
   if(preGameCountDown->isDone()){
     gameCountDown->start();
     gameState = RUNGAME;
   }
}

void runGame () {
   lcd.setCursor(0,0);
   lcd.print("Match Colors");
   lcd.setCursor(0,1);
   lcd.print(gameCountDown->seconds());
   
   // TODO: set center LED to roundColor
   // TODO: read the mode switch input
   // TODO: read the color change dial
   // TODO: read the lock buttons
   
   // TODO: set player's lock status
   // p1->lockInGuess();
   // p2->lockInGuess();
   
   // TODO: set player's color mode leds
   // p1->colorMode()
   // p2->colorMode()
   
   // TODO: set player's result led
   // p1->colorChange(int [how much it changed]
   // p2->colorChange(int [how much it changed]   


   if(gameCountDown->isDone() || (p1->locked && p2->locked)){
      if(!p1->locked) {
        p1->lockInGuess();
      }
      if(!p2->locked) {
        p2->lockInGuess();
      }

      p1->score = roundColor->calculateColorScore(p1->color);
      p2->score = roundColor->calculateColorScore(p2->color);

      gameState = RESULTS;
   }
}

void results () {
   lcd.setCursor(0,0);
   lcd.print("Game Over");
   delay(2000);

   lcd.setCursor(0,0);
   lcd.print("P1: " + p1->score);
   lcd.setCursor(0,1);
   lcd.print("P2: " + p2->score);
   delay(2000);

   

   reset();
}
