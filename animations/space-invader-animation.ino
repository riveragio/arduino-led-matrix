// 8x8 LED Matrix - Space Invader Animation

const int latchPin = 8;
const int clockPin = 12;
const int dataPin = 11;

byte ledStatus[2];

byte invader1[8] = {
  0b00100100,
  0b00011000,
  0b01111110,
  0b11011011,
  0b11111111,
  0b10100101,
  0b10100101,
  0b00000000
};

byte invader2[8] = {
  0b00100100,
  0b10011001,
  0b11111111,
  0b11011011,
  0b11111111,
  0b00100100,
  0b01000010,
  0b00000000
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

  displayFrame(invader1, 350);
  displayFrame(invader2, 350);
}