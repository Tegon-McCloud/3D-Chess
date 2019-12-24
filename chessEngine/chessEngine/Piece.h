#pragma once
#include <string>

class Piece {
public:
	virtual void move(int* field[5][5][5], int x, int y, int z) = 0;
	virtual void printMoves(int* field[5][5][5], int x, int y, int z) = 0;
	virtual std::string getMoves(int* field[5][5][5], int x, int y, int z) = 0;
};