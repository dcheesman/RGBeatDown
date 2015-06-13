int first = 9;
int second = 10;
int third = 11;

int redPin = 6;
int greenPin = 5;
int bluePin = 3;

int buttonPin = 2;
int buttonState = 0;

int lightState = 0;

void setup() {
  Serial.begin(9600);
  pinMode(first, OUTPUT);
  pinMode(second, OUTPUT);
  pinMode(third, OUTPUT);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  pinMode(buttonPin, INPUT);
}

void loop() {

    // Read the state of the pushbutton value
    buttonState = digitalRead(buttonPin);

    Serial.print(lightState);

    if (buttonState == HIGH) {
      delay(1000);
      lightState++;
    }

    if (lightState == 1) {
      digitalWrite(first, HIGH);
      analogWrite(bluePin, 255);
    }

    if (lightState == 2) {
      digitalWrite(second, HIGH);
      analogWrite(redPin, 255);
    }

    if (lightState == 3) {
      digitalWrite(third, HIGH);
      analogWrite(greenPin, 255);
    }

    if (lightState >= 4) {
      lightState = 0;
      clear();
    }
}

void clear() {
    digitalWrite(first, LOW);
    digitalWrite(second, LOW);
    digitalWrite(third, LOW);

    analogWrite(redPin, 0);
    analogWrite(bluePin, 0);
    analogWrite(greenPin, 0);
}