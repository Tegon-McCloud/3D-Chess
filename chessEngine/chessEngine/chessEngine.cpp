#include <iostream>
#include "Game.h"
#include <sstream>

int main() {
	Game g = Game();
	g.printEntireField();
	while (true) {
		std::stringstream ss;
		std::string move;
		std::cin >> move;
		if (move.length() == 3) {
			std::cout << g.getPieceMoves((int) move[0] - '0', (int) move[1] - '0', (int) move[2] - '0') << "\n";
		}
		if (move.length() == 6) {
			ss << move[0] << ' ' << move[1] << ' ' << move[2] << ' ' << move[3] << ' ' << move[4] << ' ' << move[5];
			system("CLS");
			std::cout << g.move(ss) << "\n";
			g.printEntireField();
		}
	}
}