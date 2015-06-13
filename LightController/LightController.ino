#include "Ai_WS2811.h"

#define LED_DATA_PIN 8
#define NUM_LEDS 10

#define P1_SELECT_BUTTON_PIN 7
int P1_POSITION = 0;
int P1_COLOR = 1;
int p1ButtonState = 0;

#define P2_SELECT_BUTTON_PIN 2
int P2_POSITION = 0;
int P2_COLOR = 9;
int p2ButtonState = 0;

// Global Middle Master Color LED
#define GLOBAL_COLOR 5

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
  
  delay(2000);
  
  // Set global LED
  randomizeGlobalLed();
  
  // Set starting position for players and light LED
  initPlayerStartingPosition();

  pinMode(P1_SELECT_BUTTON_PIN, INPUT);
  pinMode(P2_SELECT_BUTTON_PIN, INPUT);
}

void clearLeds() {
  for (int i=0; i<NUM_LEDS; ++i) {
     setLedColor(i, 0, 0, 0);
     ws2811.sendLedData();
  }
}

void randomizeGlobalLed() {
    int r = random(0, 255);  
    int g = random(0, 255);
    int b = random(0, 255);
    
    setLedColor(GLOBAL_COLOR, r, g, b);
    ws2811.sendLedData();
}

void initPlayerStartingPosition() {
    P1_POSITION = 4;
    P2_POSITION = 6;
    
    setLedColor(P1_POSITION, 255, 0, 0);
    setLedColor(P2_POSITION, 255, 0, 0);
    ws2811.sendLedData();
}

void movePlayerPosition(int player) {
  
  if (player == 1) {
    
    setLedColor(P1_POSITION, 0, 0, 0);
    
    P1_POSITION--;
    if(P1_POSITION <= 1) {
      P1_POSITION = 4;
    }
    
    if (P1_POSITION == 4) {
      setLedColor(P1_POSITION, 255, 0, 0);  
    }
    
    if (P1_POSITION == 3) {
      setLedColor(P1_POSITION, 0, 255, 0);  
    }
    
    if (P1_POSITION == 2) {
      setLedColor(P1_POSITION, 0, 0, 255);  
    }
    
  } else {
    
    setLedColor(P2_POSITION, 0, 0, 0);
    
    P2_POSITION++;
    if(P2_POSITION >= 9) {
      P2_POSITION = 6;
    }
    
    if (P2_POSITION == 6) {
      setLedColor(P2_POSITION, 255, 0, 0);  
    }
    
    if (P2_POSITION == 7) {
      setLedColor(P2_POSITION, 0, 255, 0);  
    }
    
    if (P2_POSITION == 8) {
      setLedColor(P2_POSITION, 0, 0, 255);  
    }
    
  } 
  
  ws2811.sendLedData();
}

void loop() {
    
    // Read the state of the player button values
    p1ButtonState = digitalRead(P1_SELECT_BUTTON_PIN);
    p2ButtonState = digitalRead(P2_SELECT_BUTTON_PIN);
    
    if (p1ButtonState == HIGH) {
      delay(1000);
      movePlayerPosition(1);
    }
    
    if (p2ButtonState == HIGH) {
      delay(1000);
      movePlayerPosition(2);
    }
}

void setLedColor(int led_index, int r, int g, int b) {
  leds[led_index].r = constrain((int)255*r,0,255);
  leds[led_index].g = constrain((int)255*g,0,255);
  leds[led_index].b = constrain((int)255*b,0,255);
  ws2811.sendLedData();
}

