#include "Game.h"

Game::Game() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			for (int k = 0; k < 5; k++) {
				setPieceId(i, j, k, ids["Empty"]);
			}
		}
	}
}

int Game::getPieceId(int x, int y, int z) {
	return field[x][y][z];
}

void Game::setPieceId(int x, int y, int z, int id) {
	field[x][y][z] = id;
}