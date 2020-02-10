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


	setPieceId(0, 4, 3, ids["Unicorn"]);
	setPieceColour(0, 4, 3, 0);
	setPieceId(1, 4, 3, ids["Bishop"]);
	setPieceColour(1, 4, 3, 0);
	setPieceId(2, 4, 3, ids["Queen"]);
	setPieceColour(2, 4, 3, 0);
	setPieceId(3, 4, 3, ids["Unicorn"]);
	setPieceColour(3, 4, 3, 0);
	setPieceId(4, 4, 3, ids["Bishop"]);
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
};

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
};

int Game::getPieceId(int x, int y, int z) {
	return field[x][y][z];
};

void Game::setPieceId(int x, int y, int z, int id) {
	field[x][y][z] = id;
};

int Game::getPieceColour(int x, int y, int z) {
	return colour[x][y][z];
};

void Game::setPieceColour(int x, int y, int z, int colour) {
	Game::colour[x][y][z] = colour;
};

std::string Game::getPieceMoves(int x, int y, int z) {
	if (getPieceColour(x, y, z) == -1) {
		return "No piece on the selected square";
	}
	if (getPieceColour(x, y, z) != colourToMove) {
		return "This is not your colour";
	}
	if (Piece::getMoves(colour, field, x, y, z, getPieceColour(x, y, z), getPieceId(x, y, z)) == "") {
		return "This piece can't move";
	}
	return Piece::getMoves(colour, field, x, y, z, getPieceColour(x, y, z), getPieceId(x, y, z));
};

int Game::movePiece(int xFrom, int yFrom, int zFrom, int xTo, int yTo, int zTo) {
	if (getPieceId(xTo, yTo, zTo) == ids["King"]) {
		if (getPieceColour(xTo, yTo, zTo) == 1) {
			return 1;
		}
		if (getPieceColour(xTo, yTo, zTo) == 0) {
			return 0;
		}
	}
	setPieceId(xTo, yTo, zTo, getPieceId(xFrom, yFrom, zFrom));
	setPieceColour(xTo, yTo, zTo, getPieceColour(xFrom, yFrom, zFrom));
	setPieceId(xFrom, yFrom, zFrom, ids["Empty"]);
	setPieceColour(xFrom, yFrom, zFrom, -1);
	return -1;
};

std::string Game::move(std::stringstream& ss) {
	//TODO error checking perhaps, but maybe not needed
	int xFrom, yFrom, zFrom, xTo, yTo, zTo;
	ss >> xFrom;
	ss >> yFrom;
	ss >> zFrom;
	ss >> xTo;
	ss >> yTo;
	ss >> zTo;
	std::string movesOfPiece = getPieceMoves(xFrom, yFrom, zFrom);
	if (movesOfPiece == "No piece on the selected square") {
		return movesOfPiece;
	}
	if (movesOfPiece == "This is not your colour") {
		return movesOfPiece;
	}
	if (movesOfPiece == "This piece can't move") {
		return movesOfPiece;
	}
	bool canMove = false;
	for (int i = 0; i < movesOfPiece.length(); i+=4) {
		std::stringstream ss;
		ss << movesOfPiece[i] << ' ' << movesOfPiece[i + 1] << ' ' << movesOfPiece[i + 2] << ' ';
		int xCurr, yCurr, zCurr;
		ss >> xCurr;
		ss >> yCurr;
		ss >> zCurr;
		if (xTo == xCurr && yTo == yCurr && zTo == zCurr) {
			canMove = true;
		}
	}
	if (!canMove) {
		return "You can't move to the selected square";
	}
	int moveTemp = movePiece(xFrom, yFrom, zFrom, xTo, yTo, zTo);
	if (moveTemp != -1) {
		if (moveTemp == 1) {
			return "VW";	//Victory White
		}
		if (moveTemp == 0) {
			return "VB";	//Victory Black
		}
	}
	colourToMove = (colourToMove - 1)*-1;
	return "You moved :)";
};