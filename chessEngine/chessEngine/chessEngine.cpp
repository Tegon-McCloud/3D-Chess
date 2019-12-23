#include <iostream>
#include "Game.h"

int main() {

	Game g = Game();
	std::cout << g.getPieceId(3,4,2) << "\n";
}