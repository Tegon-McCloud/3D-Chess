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
	Server s("8877");
	std::string msg;
	s.sendMSG(1, "s:w;");
	s.sendMSG(0, "s:b;");

	s.sendMSG( 0, g.colourToMove == 1 ? "t:w;" : "t:b;" );
	s.sendMSG( 1, g.colourToMove == 1 ? "t:w;" : "t:b;" );

	while (true) {

		s.getMSG(g.colourToMove, msg);
		switch (msg[0]) {
		case 'p':
		{
			msg.erase(0, 2);
			Position pos(msg);
			if (g.getPieceMoves(pos.xyz.x, pos.xyz.y, pos.xyz.z)[0] == '0' ||
				g.getPieceMoves(pos.xyz.x, pos.xyz.y, pos.xyz.z)[0] == '1' ||
				g.getPieceMoves(pos.xyz.x, pos.xyz.y, pos.xyz.z)[0] == '2' ||
				g.getPieceMoves(pos.xyz.x, pos.xyz.y, pos.xyz.z)[0] == '3' ||
				g.getPieceMoves(pos.xyz.x, pos.xyz.y, pos.xyz.z)[0] == '4') {
				s.sendMSG(g.colourToMove, std::string("p:") + listToAlg(g.getPieceMoves(pos.xyz.x, pos.xyz.y, pos.xyz.z)));
			}
			else {
				s.sendMSG(g.colourToMove, "p:;");
			}
		}
			break;

		case 'm':
		{
			std::string msgCopy(msg);
			msgCopy += ";";
			msg.erase(0, 2);
			Position from(msg);
			msg.erase(0, 3);
			Position to(msg);
			//TODO error checking if hacked client
			std::stringstream ss;
			ss << from.xyz.x << " " << from.xyz.y << " " << from.xyz.z << " " << to.xyz.x << " " << to.xyz.y << " " << to.xyz.z;
			std::string move = g.move(ss);
			if (move[0] == 'Y' ||
				move[0] == 'Y' ||
				move[0] == 'Y' ||
				move[0] == 'Y' ||
				move[0] == 'Y') {

				s.sendMSG(0, msgCopy);
				s.sendMSG(1, msgCopy);

				s.sendMSG(0, g.colourToMove == 1 ? "t:w;" : "t:b;");
				s.sendMSG(1, g.colourToMove == 1 ? "t:w;" : "t:b;");
			}
		}
			break;
		}
	}
}