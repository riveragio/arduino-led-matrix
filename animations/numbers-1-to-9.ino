// 8x8 LED Matrix - Numbers 1 to 9

const int latchPin = 8;
const int clockPin = 12;
const int dataPin = 11;

byte ledStatus[2];

const byte numbers[9][8] = {

  // 1
  {
    0b00011000,
    0b00111000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b00011000,
    0b01111110,
    0
  },

  // 2
  {
    0b00111100,
    0b01100110,
    0b00000110,
    0b00001100,
    0b00110000,
    0b01100000,
    0b01111110,
    0
  },

  // 3
  {
    0b00111100,
    0b01100110,
    0b00000110,
    0b00011100,
    0b00000110,
    0b01100110,
    0b00111100,
    0
  },

  // 4
  {
    0b00001100,
    0b00011100,
    0b00101100,
    0b01001100,
    0b01111110,
    0b00001100,
    0b00001100,
    0
  },

  // 5
  {
    0b01111110,
    0b01100000,
    0b01111100,
    0b00000110,
    0b00000110,
    0b01100110,
    0b00111100,
    0
  },

  // 6
  {
    0b00111100,
    0b01100000,
    0b01100000,
    0b01111100,
    0b01100110,
    0b01100110,
    0b00111100,
    0
  },

  // 7
  {
    0b01111110,
    0b00000110,
    0b00001100,
    0b00011000,
    0b00110000,
    0b00110000,
    0b00110000,
    0
  },

  // 8
  {
    0b00111100,
    0b01100110,
    0b01100110,
    0b00111100,
    0b01100110,
    0b01100110,
    0b00111100,
    0
  },

  // 9
  {
    0b00111100,
    0b01100110,
    0b01100110,
    0b00111110,
    0b00000110,
    0b00001100,
    0b00111000,
    0
  }
};

void shiftOutHC595() {
  digitalWrite(latchPin, LOW);

  shiftOut(dataPin, clockPin, MSBFIRST, ledStatus[0]);
  shiftOut(dataPin, clockPin, MSBFIRST, ledStatus[1]);

  digitalWrite(latchPin, HIGH);
}

void displayNumber(const byte number[8], int duration) {
  unsigned long start = millis();

  while (millis() - start < duration) {

    for (int row = 0; row < 8; row++) {

      ledStatus[0] = ~number[row];
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

  for (int i = 0; i < 9; i++) {
    displayNumber(numbers[i], 500);
  }

  delay(500);
}