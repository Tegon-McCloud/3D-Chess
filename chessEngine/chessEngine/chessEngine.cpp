#include <iostream>
#include "Game.h"

int main() {
	Game g = Game();
	g.printEntireField();
	g.movePiece(0,0,0,2,2,2);
	g.printEntireField();
}