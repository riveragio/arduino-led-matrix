// 8x8 LED Matrix - Pong Animation

const int latchPin = 8;
const int clockPin = 12;
const int dataPin = 11;

byte ledStatus[2];

int ballX = 3;
int ballY = 3;

int dx = 1;
int dy = 1;

int leftPaddle = 2;
int rightPaddle = 3;

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

  byte frame[8] = {0};

  // Left paddle
  frame[leftPaddle] |= 0b10000000;
  frame[leftPaddle + 1] |= 0b10000000;
  frame[leftPaddle + 2] |= 0b10000000;

  // Right paddle
  frame[rightPaddle] |= 0b00000001;
  frame[rightPaddle + 1] |= 0b00000001;
  frame[rightPaddle + 2] |= 0b00000001;

  // Ball
  frame[ballY] |= (1 << (7 - ballX));

  displayFrame(frame, 90);

  ballX += dx;
  ballY += dy;

  if (ballY <= 0 || ballY >= 7) {
    dy = -dy;
  }

  if (ballX <= 1) {
    dx = 1;
  }

  if (ballX >= 6) {
    dx = -1;
  }

  // Automatically follow the ball
  leftPaddle = constrain(ballY - 1, 0, 5);
  rightPaddle = constrain(ballY - 1, 0, 5);
}