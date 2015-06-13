#include "Player.h"
#include "Color.h"

void Player::init () {
  reset();
  color = new Color();
  score = 0;
}

void Player::reset() {
  color->red = 0;
  color->green = 0;
  color->blue = 0;
  locked = false;
}

void Player::nextMode() {
  
  if (isIncrement) {
    colorMode++;  
  } else {
    colorMode--;
  }
  colorMode %= 3;
}

int Player::currentPosition() {
  return startPosition + colorMode;
}

void Player::colorChange(int delta) {
  switch (colorMode) {
    case RED:
      color->red += delta;
      color->red = constrain(color->red, 0, 255);
      break;
    case GREEN:
      color->green += delta;
      color->green = constrain(color->green, 0, 255);
      break;
    case BLUE:
      color->blue += delta;
      color->blue = constrain(color->blue, 0, 255);
      break;
  }
}

void Player::lockInGuess () {
  locked = true;
  locktime = millis();
}
