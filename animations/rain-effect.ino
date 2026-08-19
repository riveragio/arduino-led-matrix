// 8x8 LED Matrix - Rain Animation

const int latchPin = 8;
const int clockPin = 12;
const int dataPin = 11;

const int HC595_COUNT = 2;

byte ledStatus[HC595_COUNT] = {0, 0};

byte frame[8] = {
  0, 0, 0, 0,
  0, 0, 0, 0
};

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  randomSeed(analogRead(A0));
}

void shiftOutHC595() {
  digitalWrite(latchPin, LOW);

  for (int i = 0; i < HC595_COUNT; i++) {
    shiftOut(dataPin, clockPin, MSBFIRST, ledStatus[i]);
  }

  digitalWrite(latchPin, HIGH);
}

void displayFrame(int duration) {
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

  // Move everything downward
  for (int row = 7; row > 0; row--) {
    frame[row] = frame[row - 1];
  }

  // Create random LEDs at top
  frame[0] = 0;

  if (random(100) < 70) {
    int x = random(8);

    frame[0] |= (1 << x);
  }

  if (random(100) < 30) {
    int x = random(8);

    frame[0] |= (1 << x);
  }

  displayFrame(100);
}