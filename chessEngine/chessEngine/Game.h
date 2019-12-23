#pragma once
#include "Piece.h"
#include "Bishop.h"
#include <unordered_map>

class Game {
public:
	Game();
	int getPieceId(int x, int y, int z);
	void setPieceId(int x, int y, int z, int id);

private:
	int field[5][5][5];
	std::unordered_map<std::string, int> ids = {
		{"Bishop", 0},
		{"Pawn", 1},
		{"Rook", 2},
		{"Empty", 3}
	};
};