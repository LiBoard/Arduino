/* LiBoard
 * Copyright (C) 2021 Philipp Leclercq
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3 as published by
 * the Free Software Foundation.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>. */

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
