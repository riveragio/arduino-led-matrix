// 8x8 LED Matrix - Pac-Man Animation

const int latchPin = 8;
const int clockPin = 12;
const int dataPin = 11;

byte ledStatus[2];

byte pacmanOpen[8] = {

  0b00111100,
  0b01111110,
  0b11111000,
  0b11100000,
  0b11111000,
  0b01111110,
  0b00111100,
  0
};

byte pacmanClosed[8] = {

  0b00111100,
  0b01111110,
  0b11111111,
  0b11111111,
  0b11111111,
  0b01111110,
  0b00111100,
  0
};

void setup() {

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void shiftOutHC595() {

  digitalWrite(latchPin, LOW);

  shiftOut(dataPin, clockPin, MSBFIRST, ledStatus[0]);
  shiftOut(dataPin, clockPin, MSBFIRST, ledStatus[1]);

  digitalWrite(latchPin, HIGH);
}

void displayFrame(byte frame[8], int duration) {

  unsigned long start = millis();

  while (millis() - start < duration) {

    for (int row = 0; row < 8; row++) {

      ledStatus[0] = ~frame[row];
      ledStatus[1] = (1 << row);

      shiftOutHC595();

      delay(2);
    }
  }
}

void loop() {

  displayFrame(pacmanOpen, 180);

  displayFrame(pacmanClosed, 180);
}