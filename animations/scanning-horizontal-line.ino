// 8x8 LED Matrix - Horizontal Scanner

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

  // Top to bottom
  for (int y = 0; y < 8; y++) {

    for (int i = 0; i < 8; i++)
      frame[i] = 0;

    frame[y] = 0xFF;

    displayFrame(frame, 100);
  }

  // Bottom to top
  for (int y = 6; y > 0; y--) {

    for (int i = 0; i < 8; i++)
      frame[i] = 0;

    frame[y] = 0xFF;

    displayFrame(frame, 100);
  }
}