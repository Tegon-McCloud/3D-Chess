#pragma once
#include "Piece.h"

class Bishop : public Piece {
public:
	void move(int* field[5][5][5], int x, int y, int z) override;
	void printMoves(int* field[5][5][5], int x, int y, int z) override;
	std::string getMoves(int* field[5][5][5], int x, int y, int z) override;
};