#include <LiquidCrystal.h>
#include "Color.h"
#include "Player.h"
#include "CountDown.h"
#include "Ai_WS2811.h"

// TODO: initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define LED_DATA_PIN 8
#define NUM_LEDS 10
#define GOAL_COLOR_PIN 5

#define P1_SELECT_BUTTON_PIN 7
#define P1_START_POS 4
int p1ButtonState = 0;

#define P2_SELECT_BUTTON_PIN 2
#define P2_START_POS 6
int p2ButtonState = 0;

const int PREGAME = 0;
const int RUNGAME = 1;
const int RESULTS = 2;

int gameState;

int preGameMillis = 200;
int gameMillis = 20000;


Color* goalColor;
Player* p1;
Player* p2;
CountDown* preGameCountDown;
CountDown* gameCountDown;

Ai_WS2811 ws2811;

struct CRGB {
  unsigned char g;
  unsigned char r;
  unsigned char b;
} *leds;

void setup() {
    ws2811.init(LED_DATA_PIN, NUM_LEDS);
  
    leds = (struct CRGB*)ws2811.getRGBData();
    
    // Initializes LEDS to 0
    clearLeds();
  
    goalColor = new Color();
    lcd.begin(16, 2);
    lcd.print("RGBeat Down");
    lcd.setCursor(0, 1);
    lcd.print("Get Ready!");
    delay(2000);
    reset();
    
    pinMode(P1_SELECT_BUTTON_PIN, INPUT);
    pinMode(P2_SELECT_BUTTON_PIN, INPUT);
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
    p1->startPosition = P1_START_POS;
    
    p2 = new Player();
    p2->startPosition = P2_START_POS;

    gameCountDown = new CountDown();
    gameCountDown->init(gameMillis);
    preGameCountDown = new CountDown();
    preGameCountDown->init(preGameMillis);
    preGameCountDown->start();
    gameState = PREGAME;

    goalColor->randomize();
    setLedColor(GOAL_COLOR_PIN, goalColor->red, goalColor->green, goalColor->blue);
    ws2811.sendLedData();
    
    // Light up player starting positions
    setLedColor(p1->startPosition, 255, 0, 0);
    setLedColor(p2->startPosition, 255, 0, 0);
}

void preGame () {
   lcd.setCursor(0,0);
   lcd.print("Staring in");
   lcd.setCursor(0,1);
   //lcd.print(preGameCountDown->seconds());
//   if(preGameCountDown->isDone()){
//     gameCountDown->start();
//     gameState = RUNGAME;
//   }
   gameState = RUNGAME;
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
   
   // Read the state of the player button values
    p1ButtonState = digitalRead(P1_SELECT_BUTTON_PIN);
    p2ButtonState = digitalRead(P2_SELECT_BUTTON_PIN);
    
    if (p1ButtonState == HIGH) {
      delay(1000);
      p1->nextMode();
      setLedColor(p1->currentPosition(), 255, 0, 0);
    }
    
    if (p2ButtonState == HIGH) {
      delay(1000);
      p2->nextMode();
      setLedColor(p2->currentPosition(), 255, 0, 0);
    }


   if(gameCountDown->isDone() || (p1->locked && p2->locked)){
      if(!p1->locked) {
        p1->lockInGuess();
      }
      if(!p2->locked) {
        p2->lockInGuess();
      }

      p1->score = goalColor->calculateColorScore(p1->color);
      p2->score = goalColor->calculateColorScore(p2->color);

      gameState = RESULTS;
   }
   
   ws2811.sendLedData();
}

void setLedColor(int led_index, int r, int g, int b) {
  leds[led_index].r = constrain((int)255*r,0,255);
  leds[led_index].g = constrain((int)255*g,0,255);
  leds[led_index].b = constrain((int)255*b,0,255);
  ws2811.sendLedData();
}

void clearLeds() {
  for (int i=0; i<NUM_LEDS; ++i) {
     setLedColor(i, 0, 0, 0);
     ws2811.sendLedData();
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
