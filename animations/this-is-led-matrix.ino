// 8x8 LED Matrix - Scroll "THIS IS LED MATRIX"

const int latchPin = 8;
const int clockPin = 12;
const int dataPin = 11;

byte ledStatus[2];

const byte font[][5] = {

  // Space
  {0x00,0x00,0x00,0x00,0x00},

  // A
  {0x7E,0x11,0x11,0x11,0x7E},

  // D
  {0x7F,0x41,0x41,0x22,0x1C},

  // E
  {0x7F,0x49,0x49,0x49,0x41},

  // H
  {0x7F,0x08,0x08,0x08,0x7F},

  // I
  {0x00,0x41,0x7F,0x41,0x00},

  // L
  {0x7F,0x40,0x40,0x40,0x40},

  // M
  {0x7F,0x02,0x0C,0x02,0x7F},

  // R
  {0x7F,0x09,0x19,0x29,0x46},

  // S
  {0x46,0x49,0x49,0x49,0x31},

  // T
  {0x01,0x01,0x7F,0x01,0x01},

  // X
  {0x63,0x14,0x08,0x14,0x63}
};

void shiftOutHC595() {
  digitalWrite(latchPin, LOW);

  shiftOut(dataPin, clockPin, MSBFIRST, ledStatus[0]);
  shiftOut(dataPin, clockPin, MSBFIRST, ledStatus[1]);

  digitalWrite(latchPin, HIGH);
}

void display(byte frame[8], int duration) {
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

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  // For now this is better implemented using the
  // full alphabet sketch below.
}