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

LiBoard::LiBoard() : LiBoard(16, 10, nullptr) {}

LiBoard::LiBoard(const unsigned char _CLK_PIN, const unsigned char _SER_PIN,
	const unsigned char _INPUT_PINS[8]) :
	CLK_PIN(_CLK_PIN), SER_PIN(_SER_PIN) {
	if (_INPUT_PINS)
		memcpy(INPUT_PINS, _INPUT_PINS, sizeof(INPUT_PINS));
	initializeBoard();
}

void LiBoard::initializeBoard() {
	pinMode(CLK_PIN, OUTPUT);
	pinMode(SER_PIN, OUTPUT);
	digitalWrite(CLK_PIN, LOW);
	digitalWrite(SER_PIN, LOW);

	for (unsigned char i = 0; i < 8; ++i)
		clockPulse();

	clockPulse(HIGH);
}

void LiBoard::clockPulse() {
	digitalWrite(CLK_PIN, HIGH);
	digitalWrite(CLK_PIN, LOW);
}

void LiBoard::clockPulse(bool data) {
	digitalWrite(SER_PIN, data);
	clockPulse();
}

void LiBoard::getData() {
	for (unsigned char file = 0; file < 8; ++file) {
		clockPulse(file == 7);
		//IMPORTANT as it gives the shift register time to update
		delayMicroseconds(200);
		for (unsigned char rank = 0; rank < 8; ++rank) {
				values[getIndex(file, rank)] = analogRead(INPUT_PINS[rank]);
		}
	}
}

unsigned char LiBoard::getIndex(unsigned char file, unsigned char rank) {
    //Little-endian Rank-File Mapping
    return (rank * 8) + file;
}

unsigned long long LiBoard::getBinaryBoard(unsigned short threshold) {
	getData();
	unsigned long long binBoard = 0;
	for (unsigned char i = 0; i<64; ++i)
		binBoard |= (((unsigned long long) (values[i]<=threshold)) << i);
	return binBoard;
}

bool LiBoard::getSquareOccupancy(unsigned char file, unsigned char rank, long long binaryBoard) {
	return (bool)((binaryBoard>>getIndex(file, rank))&1);
}
