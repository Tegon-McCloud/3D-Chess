#pragma once
#include "Piece.h"
#include <unordered_map>

class Game {
public:
	Game();
	void printEntireField();
	std::string getPieceMoves(int x, int y, int z);
	std::string move(std::stringstream& s);
	int colourToMove = 1;

private:
	int field[5][5][5];
	int colour[5][5][5];	//0 is black, 1 is white and -1 is none
	std::unordered_map<std::string, int> ids = {
		{"Empty", 0},
		{"Pawn", 1},
		{"Knight", 2},
		{"Bishop", 3},
		{"Rook", 4},
		{"Unicorn", 5},
		{"Queen", 6},
		{"King", 7}
	};
	// måske endnu et map som er fra int til bogstaver, kinda, altså position 1,4,1 er jo B5b eller sådan noget, og det her skal måske ind i bishop eller piece eller noget

	int movePiece(int xFrom, int yFrom, int zFrom, int xTo, int yTo, int zTo);
	void setPieceId(int x, int y, int z, int id);
	void setPieceColour(int x, int y, int z, int colour);
	int getPieceId(int x, int y, int z);
	int getPieceColour(int x, int y, int z);
};