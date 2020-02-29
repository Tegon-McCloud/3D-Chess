#pragma once
#include <string>

class Piece{
public:
	static void move(int colours[5][5][5], int field[5][5][5], int x, int y, int z, int colour, int type);
	static void printMoves(int colours[5][5][5], int field[5][5][5], int x, int y, int z, int colour, int type);
	static std::string getMoves(int colours[5][5][5], int field[5][5][5], int x, int y, int z, int colour, int type);

private:
	static std::string getBishopMoves(int colours[5][5][5], int field[5][5][5], int x, int y, int z, int colour);
	static std::string getRookMoves(int colours[5][5][5], int field[5][5][5], int x, int y, int z, int colour);
	static std::string getUnicornMoves(int colours[5][5][5], int field[5][5][5], int x, int y, int z, int colour);
};