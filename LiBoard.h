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

#ifndef LIBOARD_H
#define LIBOARD_H

#include <Arduino.h>

class LiBoard {
public:
	LiBoard();
	LiBoard(const unsigned char _CLK_PIN, const unsigned char _SER_PIN, const unsigned char _INPUT_PINS[8]);
	const unsigned char SER_PIN;
	const unsigned char CLK_PIN;
	unsigned char INPUT_PINS[8] = {0, 1, 2, 3, 9, 8, 7, 6};
	unsigned short values[64];

	void getData();
	unsigned char getIndex(unsigned char file, unsigned char rank);
	unsigned long long getBinaryBoard(unsigned short threshold);
	bool getSquareOccupancy(unsigned char file, unsigned char rank, long long binaryBoard);
private:
	void clockPulse();
	void clockPulse(bool data);
	void initializeBoard();
};

#endif
