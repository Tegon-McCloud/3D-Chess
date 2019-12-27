#include <iostream>
#include "Game.h"

int main() {
	Game g = Game();
	g.printEntireField();
	g.movePiece(2,2,3,2,2,2);
}