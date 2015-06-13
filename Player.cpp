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
  colorMode++;
  colorMode %= 3;
}

void Player::lockInGuess () {
  locked = true;
  locktime = millis();
}
