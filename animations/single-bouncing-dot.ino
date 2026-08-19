// 8x8 LED Matrix - Bouncing Dot

const int latchPin = 8;
const int clockPin = 12;
const int dataPin = 11;

const int HC595_COUNT = 2;

byte ledStatus[HC595_COUNT] = {0, 0};

int x = 0;
int y = 0;

int dx = 1;
int dy = 1;

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
  byte frame[8] = {
    0, 0, 0, 0,
    0, 0, 0, 0
  };

  frame[y] = (1 << x);

  displayFrame(frame, 70);

  x += dx;
  y += dy;

  if (x <= 0 || x >= 7)
    dx = -dx;

  if (y <= 0 || y >= 7)
    dy = -dy;
}