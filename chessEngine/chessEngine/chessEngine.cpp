#include <iostream>
#include "Game.h"
#include <sstream>
#include "Server.h"
#include "Util.h"

int main() {
	Game g;
	/*g.printEntireField();
	while (true) {
		std::stringstream ss;
		std::string move;
		std::cin >> move;
		if (move == "exit") {
			exit(0);
		}
		if (move.length() == 3) {
			std::cout << g.getPieceMoves((int) move[0] - '0', (int) move[1] - '0', (int) move[2] - '0') << "\n";
		}
		if (move.length() == 6) {
			ss << move[0] << ' ' << move[1] << ' ' << move[2] << ' ' << move[3] << ' ' << move[4] << ' ' << move[5];
			system("CLS");
			std::cout << g.move(ss) << "\n";
			g.printEntireField();
		}
	}*/
	std::cout << g.getPieceMoves(1, 0, 1);
	Server s("8877");
	std::string msg;
	s.sendMSG(1, "s:w;");
	s.sendMSG(0, "s:b;");
	

	while (true) {
		s.sendMSG(0, "t:w;");
		s.sendMSG(1, "t:w;");

		while (true) {
			s.getMSG(1, msg);
			switch (msg[0]) {
			case 'p':
				msg.erase(0, 2);
				Position pos(msg);
				if (g.getPieceMoves(pos.xyz.x, pos.xyz.y, pos.xyz.z)[0] == '0' || g.getPieceMoves(pos.xyz.x, pos.xyz.y, pos.xyz.z)[0] == '1' || g.getPieceMoves(pos.xyz.x, pos.xyz.y, pos.xyz.z)[0] == '2' || g.getPieceMoves(pos.xyz.x, pos.xyz.y, pos.xyz.z)[0] == '3' || g.getPieceMoves(pos.xyz.x, pos.xyz.y, pos.xyz.z)[0] == '4') {
					s.sendMSG(1, listToAlg(g.getPieceMoves(pos.xyz.x, pos.xyz.y, pos.xyz.z)));
				}
				else {
					s.sendMSG(1, ";");
				}
			}
		}
	}
}