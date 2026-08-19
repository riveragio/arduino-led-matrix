// 8x8 LED Matrix - Pulse Animation

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

  byte pulse1[8] = {
    0b00000000,
    0b00000000,
    0b00000000,
    0b00011000,
    0b00011000,
    0b00000000,
    0b00000000,
    0b00000000
  };

  byte pulse2[8] = {
    0b00000000,
    0b00000000,
    0b00111100,
    0b00100100,
    0b00100100,
    0b00111100,
    0b00000000,
    0b00000000
  };

  byte pulse3[8] = {
    0b00000000,
    0b00111100,
    0b01000010,
    0b01000010,
    0b01000010,
    0b01000010,
    0b00111100,
    0b00000000
  };

  byte pulse4[8] = {
    0b00111100,
    0b01000010,
    0b10000001,
    0b10000001,
    0b10000001,
    0b10000001,
    0b01000010,
    0b00111100
  };

  displayFrame(pulse1, 130);
  displayFrame(pulse2, 130);
  displayFrame(pulse3, 130);
  displayFrame(pulse4, 130);

  displayFrame(pulse3, 130);
  displayFrame(pulse2, 130);
}