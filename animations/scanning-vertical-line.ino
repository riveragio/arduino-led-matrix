// 8x8 LED Matrix - Vertical Scanner

const int latchPin = 8;
const int clockPin = 12;
const int dataPin = 11;

const int HC595_COUNT = 2;

byte ledStatus[HC595_COUNT] = {0, 0};

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void shiftOutHC595() {
  digitalWrite(latchPin, LOW);

  for (int i = 0; i < HC595_COUNT; i++) {
    shiftOut(dataPin, clockPin, MSBFIRST, ledStatus[i]);
  }

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
  byte frame[8];

  // Left to right
  for (int x = 0; x < 8; x++) {

    byte column = (1 << x);

    for (int row = 0; row < 8; row++) {
      frame[row] = column;
    }

    displayFrame(frame, 100);
  }

  // Right to left
  for (int x = 6; x > 0; x--) {

    byte column = (1 << x);

    for (int row = 0; row < 8; row++) {
      frame[row] = column;
    }

    displayFrame(frame, 100);
  }
}