// 8x8 LED Matrix - Tetris Falling Block

const int latchPin = 8;
const int clockPin = 12;
const int dataPin = 11;

byte ledStatus[2];

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

  for (int y = 0; y < 7; y++) {

    byte frame[8] = {0};

    // Ground blocks
    frame[7] = 0b11100111;

    // Falling 2x2 block
    frame[y] |= 0b00011000;

    if (y + 1 < 8)
      frame[y + 1] |= 0b00011000;

    displayFrame(frame, 180);
  }

  delay(300);
}