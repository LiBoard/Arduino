#include "LiBoard.h"

const unsigned short THRESHOLD = 100;

LiBoard board = LiBoard();
unsigned long long lastBinBoard = 0;
unsigned long long currentBinBoard = 0;

void writeBinaryBoard(unsigned long long binBoard) {
  for (unsigned char i = 0; i<8; ++i)
    Serial.write((unsigned char)(binBoard>>(8*(7-i))));
}

void setup() {
  delay(3000);
  Serial.begin(9600);
}

void loop() {
  currentBinBoard = board.getBinaryBoard(THRESHOLD);
  if (currentBinBoard != lastBinBoard) {
    writeBinaryBoard(currentBinBoard);
    lastBinBoard = currentBinBoard;
  }
}
