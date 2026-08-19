// 8x8 LED Matrix - Scroll "Hello, Gio"

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

// 5x7 characters
const byte H[7] = {
  0b10001,
  0b10001,
  0b10001,
  0b11111,
  0b10001,
  0b10001,
  0b10001
};

const byte E[7] = {
  0b11111,
  0b10000,
  0b10000,
  0b11110,
  0b10000,
  0b10000,
  0b11111
};

const byte L[7] = {
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b10000,
  0b11111
};

const byte O[7] = {
  0b01110,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b10001,
  0b01110
};

const byte G[7] = {
  0b01110,
  0b10001,
  0b10000,
  0b10111,
  0b10001,
  0b10001,
  0b01110
};

const byte I[7] = {
  0b11111,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b00100,
  0b11111
};

const byte COMMA[7] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b00100,
  0b00100,
  0b01000
};

const byte SPACE[7] = {
  0, 0, 0, 0, 0, 0, 0
};

void scrollCharacter(const byte character[7]) {
  byte frame[8];

  for (int offset = 8; offset >= -5; offset--) {

    for (int row = 0; row < 8; row++) {
      frame[row] = 0;
    }

    for (int y = 0; y < 7; y++) {
      for (int x = 0; x < 5; x++) {

        if (character[y] & (1 << (4 - x))) {
          int screenX = x + offset;

          if (screenX >= 0 && screenX < 8) {
            frame[y] |= (1 << (7 - screenX));
          }
        }
      }
    }

    displayFrame(frame, 50);
  }
}

void loop() {
  scrollCharacter(H);
  scrollCharacter(E);
  scrollCharacter(L);
  scrollCharacter(L);
  scrollCharacter(O);
  scrollCharacter(COMMA);
  scrollCharacter(SPACE);
  scrollCharacter(G);
  scrollCharacter(I);

  delay(500);
}