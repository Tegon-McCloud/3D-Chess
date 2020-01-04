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
		return "There is no piece on the selected square";
	}
	if (getPieceColour(x, y, z) != colourToMove) {
		return "This is not your colour";
	}
	std::string pieceMoves(Piece::getMoves(colour, field, x, y, z, getPieceColour(x, y, z), getPieceId(x, y, z)));
	//Check things
	std::stringstream pieceMoves2;
	if (whiteCheck) {
	idk:
		for (int i = 0; i < pieceMoves.length(); i += 4) {
			std::stringstream ss;
			ss << pieceMoves[i] << ' ' << pieceMoves[i + 1] << ' ' << pieceMoves[i + 2] << ' ';
			int xCurr, yCurr, zCurr;
			ss >> xCurr;
			ss >> yCurr;
			ss >> zCurr;
			int prevId = getPieceId(xCurr, yCurr, zCurr);
			movePiece(x, y, z, xCurr, yCurr, zCurr);
			setChecks();
			if (whiteCheck) {
				pieceMoves2 << xCurr << yCurr << zCurr << ' ';
				movePiece(xCurr, yCurr, zCurr, x, y, z);
				setPieceId(xCurr, yCurr, zCurr, prevId);
				setChecks();
			}
		}
		pieceMoves = pieceMoves2.str();
	}
	if (blackCheck) {
	idk2:
		for (int i = 0; i < pieceMoves.length(); i += 4) {
			std::stringstream ss;
			ss << pieceMoves[i] << ' ' << pieceMoves[i + 1] << ' ' << pieceMoves[i + 2] << ' ';
			int xCurr, yCurr, zCurr;
			ss >> xCurr;
			ss >> yCurr;
			ss >> zCurr;
			int prevId = getPieceId(xCurr, yCurr, zCurr);
			movePiece(x, y, z, xCurr, yCurr, zCurr);
			setChecks();
			if (blackCheck) {
				pieceMoves.erase(i, 4);
				movePiece(xCurr, yCurr, zCurr, x, y, z);
				setPieceId(xCurr, yCurr, zCurr, prevId);
				setChecks();
				goto idk2;
			}
		}
	}
	//TODO Checkmate checking and stalemate checking and maybe other stuff like that
	if (pieceMoves == "") {
		return "This piece can't move";
	}
	return pieceMoves;
};

void Game::movePiece(int xFrom, int yFrom, int zFrom, int xTo, int yTo, int zTo) {
	setPieceId(xTo, yTo, zTo, getPieceId(xFrom, yFrom, zFrom));
	setPieceColour(xTo, yTo, zTo, getPieceColour(xFrom, yFrom, zFrom));
	setPieceId(xFrom, yFrom, zFrom, ids["Empty"]);
	setPieceColour(xFrom, yFrom, zFrom, -1);
};

bool Game::move(std::stringstream& ss) {
	//TODO error checking perhaps, but maybe not needed
	int xFrom, yFrom, zFrom, xTo, yTo, zTo;
	ss >> xFrom;
	ss >> yFrom;
	ss >> zFrom;
	ss >> xTo;
	ss >> yTo;
	ss >> zTo;
	std::string movesOfPiece = getPieceMoves(xFrom, yFrom, zFrom);
	if (movesOfPiece[0] == 'T'){
		return false;
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
		return false;
	}

	movePiece(xFrom, yFrom, zFrom, xTo, yTo, zTo);
	colourToMove = (colourToMove - 1)*-1;
	setChecks();
	return true;
};

void Game::setChecks() {
	int wkx, wky, wkz, bkx, bky, bkz;	//wkx = white king x
	bool wNotCheck = true, bNotCheck = true;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				if (getPieceId(i, j, k) == ids["King"] && getPieceColour(i, j, k) == 1) {
					wkx = i;
					wky = j;
					wkz = k;
				}
				if (getPieceId(i, j, k) == ids["King"] && getPieceColour(i, j, k) == 0) {
					bkx = i;
					bky = j;
					bkz = k;
				}
			}
		}
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				std::string moves;
				int currentColour = getPieceColour(i, j, k);
				moves = Piece::getMoves(colour, field, i, j, k, currentColour, getPieceId(i, j, k));
				if (moves[0] != 'T') {
					for (int i = 0; i < moves.length(); i += 4) {
						std::stringstream ss;
						ss << moves[i] << ' ' << moves[i + 1] << ' ' << moves[i + 2] << ' ';
						int xCurr, yCurr, zCurr;
						ss >> xCurr;
						ss >> yCurr;
						ss >> zCurr;
						if (currentColour == 1) {
							if (xCurr == bkx && yCurr == bky && zCurr == bkz) {
								blackCheck = true;
								bNotCheck = false;
							}
						}
						if(currentColour == 0) {
							if (xCurr == wkx && yCurr == wky && zCurr == wkz) {
								whiteCheck = true;
								wNotCheck = false;
							}
						}
					}
				}
			}
		}
	}
	if (wNotCheck) {
		whiteCheck = false;
	}
	if (bNotCheck) {
		blackCheck = false;
	}
}