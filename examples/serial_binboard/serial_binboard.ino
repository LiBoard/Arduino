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
#include <string.h>

// !!! choose mode: 1 = global single value, 0 = per-square array !!!
#define USE_GLOBAL_THRESHOLD 0

#if USE_GLOBAL_THRESHOLD 
// Option 1 - Global Threshold (Applies to all photoresistors)
unsigned short THRESHOLD = 100;

#else
// Option 2 - Per-square threshold (Applies to each individual photoresistor)
unsigned short THRESHOLD[64] = {
  // A1..H1
  300, 300, 300, 300, 300, 300, 300, 300,
  // A2..H2
  300, 300, 300, 300, 300, 300, 300, 300,
  // A3..H3
  100, 100, 100, 100, 100, 100, 100, 100,
  // A4..H4
  100, 100, 100, 100, 100, 100, 100, 100,
  // A5..H5
  600, 600, 600, 600, 600, 600, 600, 600,
  // A6..H6
  600, 600, 600, 600, 600, 600, 600, 600,
  // A7..H7
  300, 300, 300, 300, 300, 300, 300, 300,
  // A8..H8
  300, 300, 300, 300, 300, 300, 300, 300,
};
#endif

bool calibrating = false;
bool quiet = false;

LiBoard board = LiBoard();
unsigned long long lastBinBoard = 0;
unsigned long long currentBinBoard = 0;

void writeBinaryBoard(unsigned long long binBoard) {
  for (unsigned char i = 0; i<8; ++i)
    Serial.write((unsigned char)(binBoard>>(8*(7-i))));
}

// print a single CSV snapshot of raw ADC values (A1..H8 in LiBoard order)
void printRawSnapshotCSV() {
  board.getData();                   // fills board.values[0..63]
  for (int i = 0; i < 64; ++i) {
    Serial.print(board.values[i]);
    if (i < 63) Serial.print(',');
  }
  Serial.println();
}

// print current threshold values as CSV
void printCurrentThreshold() {
#if USE_GLOBAL_THRESHOLD
  // Global Threshold - print one value
   Serial.println(THRESHOLD);
#else
  // Individual Thresholds - print 64 values
  for (int i = 0; i < 64; ++i) {
    Serial.print(THRESHOLD[i]);
    if (i < 63) Serial.print(',');
  }
  Serial.println();
#endif
}

void setup() {
  delay(3000);
  Serial.begin(9600);
}

void loop() {
  // Serial Monitor arguements
  if (Serial.available()) {
    int c = Serial.read();
    // if host sends '?', reply with one CSV line of raw ADC values
    if (c == '?') {
      printRawSnapshotCSV();
    }

    // if host sends '!', reply with current threshold values
    if (c == '!') {
      printCurrentThreshold();
    }

    // Toggle quiet mode (Used to silence bitboard output)
    if (c == 'q' && quiet == false) {
      quiet = true;
      Serial.println("Quiet Mode Activated!");
    }
    else if (c == 'q' && quiet == true) {
      quiet = false;
      Serial.println("Exited Quiet Mode!");
    }

    // Calibration Mode for editing THRESHOLD
    if (c == 'c') {
      calibrating = true;
      Serial.println("Calibration Mode Activated!");
    }

    while (calibrating) {
      if (Serial.available()){
        // read a whole line the user pasted
        String line = Serial.readStringUntil('\n');
        line.trim();
        if (line.length() == 0) continue;

#if USE_GLOBAL_THRESHOLD        
        // Global Threshold Calibration
        long newThreshold = line.toInt();
        THRESHOLD = (unsigned short)newThreshold;
#else
        // Per-Square Calibration
        char buf[1024];
        line.toCharArray(buf, 1024);
        char* tok = strtok(buf, ",");

        int i = 0;
        while (tok && i < 64) {
          THRESHOLD[i++] = (unsigned short)atoi(tok);
          tok = strtok(nullptr, ",");
        }
#endif
        calibrating = false;
        // eat non-numeric to avoid getting stuck
        while (Serial.available()) Serial.read();
      }
    }
  }

  // Bitboard logic for normal use
  if (!quiet && !calibrating) {
    currentBinBoard = board.getBinaryBoard(THRESHOLD);
    if (currentBinBoard != lastBinBoard) {
      writeBinaryBoard(currentBinBoard);
      lastBinBoard = currentBinBoard;
    }
  }
}
