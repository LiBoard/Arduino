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
