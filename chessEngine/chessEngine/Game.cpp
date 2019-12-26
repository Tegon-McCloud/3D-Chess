#include "Game.h"
#include <iostream>
#include <sstream>

Game::Game() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				setPieceId(i, j, k, ids["Empty"]);
				setPieceColour(i, j, k, -1);
			}
		}
	}

	//Whites pieces
	setPieceId(0, 0, 0, ids["Rook"]);
	setPieceColour(0, 0, 0, 1);
	setPieceId(1, 0, 0, ids["Knight"]);
	setPieceColour(1, 0, 0, 1);
	setPieceId(2, 0, 0, ids["King"]);
	setPieceColour(2, 0, 0, 1);
	setPieceId(3, 0, 0, ids["Knight"]);
	setPieceColour(3, 0, 0, 1);
	setPieceId(4, 0, 0, ids["Rook"]);
	setPieceColour(4, 0, 0, 1);

	setPieceId(0, 1, 0, ids["Pawn"]);
	setPieceColour(0, 1, 0, 1);
	setPieceId(1, 1, 0, ids["Pawn"]);
	setPieceColour(1, 1, 0, 1);
	setPieceId(2, 1, 0, ids["Pawn"]);
	setPieceColour(2, 1, 0, 1);
	setPieceId(3, 1, 0, ids["Pawn"]);
	setPieceColour(3, 1, 0, 1);
	setPieceId(4, 1, 0, ids["Pawn"]);
	setPieceColour(4, 1, 0, 1);


	setPieceId(0, 0, 1, ids["Bishop"]);
	setPieceColour(0, 0, 1, 1);
	setPieceId(1, 0, 1, ids["Unicorn"]);
	setPieceColour(1, 0, 1, 1);
	setPieceId(2, 0, 1, ids["Queen"]);
	setPieceColour(2, 0, 1, 1);
	setPieceId(3, 0, 1, ids["Bishop"]);
	setPieceColour(3, 0, 1, 1);
	setPieceId(4, 0, 1, ids["Unicorn"]);
	setPieceColour(4, 0, 1, 1);

	setPieceId(0, 1, 1, ids["Pawn"]);
	setPieceColour(0, 1, 1, 1);
	setPieceId(1, 1, 1, ids["Pawn"]);
	setPieceColour(1, 1, 1, 1);
	setPieceId(2, 1, 1, ids["Pawn"]);
	setPieceColour(2, 1, 1, 1);
	setPieceId(3, 1, 1, ids["Pawn"]);
	setPieceColour(3, 1, 1, 1);
	setPieceId(4, 1, 1, ids["Pawn"]);
	setPieceColour(4, 1, 1, 1);


	//Blacks pieces
	setPieceId(0, 4, 4, ids["Rook"]);
	setPieceColour(0, 4, 4, 0);
	setPieceId(1, 4, 4, ids["Knight"]);
	setPieceColour(1, 4, 4, 0);
	setPieceId(2, 4, 4, ids["King"]);
	setPieceColour(2, 4, 4, 0);
	setPieceId(3, 4, 4, ids["Knight"]);
	setPieceColour(3, 4, 4, 0);
	setPieceId(4, 4, 4, ids["Rook"]);
	setPieceColour(4, 4, 4, 0);

	setPieceId(0, 3, 4, ids["Pawn"]);
	setPieceColour(0, 3, 4, 0);
	setPieceId(1, 3, 4, ids["Pawn"]);
	setPieceColour(1, 3, 4, 0);
	setPieceId(2, 3, 4, ids["Pawn"]);
	setPieceColour(2, 3, 4, 0);
	setPieceId(3, 3, 4, ids["Pawn"]);
	setPieceColour(3, 3, 4, 0);
	setPieceId(4, 3, 4, ids["Pawn"]);
	setPieceColour(4, 3, 4, 0);


	setPieceId(0, 4, 3, ids["Bishop"]);
	setPieceColour(0, 4, 3, 0);
	setPieceId(1, 4, 3, ids["Unicorn"]);
	setPieceColour(1, 4, 3, 0);
	setPieceId(2, 4, 3, ids["Queen"]);
	setPieceColour(2, 4, 3, 0);
	setPieceId(3, 4, 3, ids["Bishop"]);
	setPieceColour(3, 4, 3, 0);
	setPieceId(4, 4, 3, ids["Unicorn"]);
	setPieceColour(4, 4, 3, 0);

	setPieceId(0, 3, 3, ids["Pawn"]);
	setPieceColour(0, 3, 3, 0);
	setPieceId(1, 3, 3, ids["Pawn"]);
	setPieceColour(1, 3, 3, 0);
	setPieceId(2, 3, 3, ids["Pawn"]);
	setPieceColour(2, 3, 3, 0);
	setPieceId(3, 3, 3, ids["Pawn"]);
	setPieceColour(3, 3, 3, 0);
	setPieceId(4, 3, 3, ids["Pawn"]);
	setPieceColour(4, 3, 3, 0);
}

void Game::printEntireField() {
	for (int i = 4; i >= 0; i--) {
		std::stringstream ss;
		for (int j = 4; j >= 0; j--) {
			for (int k = 0; k < 5; k++) {
				switch (getPieceId(k, i, j)) {
				case 0:
					ss << " ";
					break;
				case 1:
					ss << 'p';
					break;
				case 2:
					ss << 'n';
					break;
				case 3:
					ss << 'b';
					break;
				case 4:
					ss << 'r';
					break;
				case 5:
					ss << 'u';
					break;
				case 6:
					ss << 'q';
					break;
				case 7:
					ss << 'k';
					break;
				}
			}
			ss << " ";
		}
		ss << "\n";
		std::cout << ss.str();
		ss.clear();
	}
	std::cout << "\n";
}

int Game::getPieceId(int x, int y, int z) {
	return field[x][y][z];
}

void Game::setPieceId(int x, int y, int z, int id) {
	field[x][y][z] = id;
}

int Game::getPieceColour(int x, int y, int z) {
	return colour[x][y][z];
}

void Game::setPieceColour(int x, int y, int z, int colour) {
	Game::colour[x][y][z] = colour;
}

void Game::movePiece(int xFrom, int yFrom, int zFrom, int xTo, int yTo, int zTo) {
	/*if (getPieceColour(xFrom, yFrom, zFrom) == getPieceColour(xTo, yTo, zTo)) {
		return;
	}
	setPieceId(xTo, yTo, zTo, getPieceId(xFrom, yFrom, zFrom));
	setPieceColour(xTo, yTo, zTo, getPieceColour(xFrom, yFrom, zFrom));
	setPieceId(xFrom, yFrom, zFrom, ids["Empty"]);
	setPieceColour(xFrom, yFrom, zFrom, -1);*/
	// above is the good stuff
	// also good stuff 1 line below
	//Piece::printMoves(colour, field, xFrom, yFrom, zFrom, getPieceColour(xFrom, yFrom, zFrom), getPieceId(xFrom, yFrom, zFrom));
	Piece::printMoves(colour, field, xFrom, yFrom, zFrom, 1, 3);
}