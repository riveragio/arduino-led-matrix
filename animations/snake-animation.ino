// 8x8 LED Matrix - Snake Animation

const int latchPin = 8;
const int clockPin = 12;
const int dataPin = 11;

byte ledStatus[2];

struct Point {
  int x;
  int y;
};

Point snake[10];

int length = 6;

void setup() {

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  for (int i = 0; i < length; i++) {
    snake[i].x = i;
    snake[i].y = 3;
  }
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

  for (int x = 0; x < 8; x++) {

    byte frame[8] = {0};

    // move body
    for (int i = length - 1; i > 0; i--) {
      snake[i] = snake[i - 1];
    }

    snake[0].x = x;
    snake[0].y = 3;

    // draw snake
    for (int i = 0; i < length; i++) {

      int sx = snake[i].x;
      int sy = snake[i].y;

      if (sx >= 0 && sx < 8 &&
          sy >= 0 && sy < 8) {

        frame[sy] |= (1 << (7 - sx));
      }
    }

    displayFrame(frame, 100);
  }
}