#pragma once
#include <string>

class Piece {
public:
	virtual void move(int* colours[5][5][5], int* field[5][5][5], int x, int y, int z, int colour) = 0;
	virtual void printMoves(int* colours[5][5][5], int* field[5][5][5], int x, int y, int z, int colour) = 0;
	virtual std::string getMoves(int* colours[5][5][5], int* field[5][5][5], int x, int y, int z, int colour) = 0;
};