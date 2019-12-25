#pragma once
#include "Piece.h"

class Bishop : public Piece {
public:
	Bishop();
	void move(int* colours[5][5][5], int* field[5][5][5], int x, int y, int z, int colour) override;
	void printMoves(int* colours[5][5][5], int* field[5][5][5], int x, int y, int z, int colour) override;
	std::string getMoves(int* colours[5][5][5], int* field[5][5][5], int x, int y, int z, int colour) override;
};