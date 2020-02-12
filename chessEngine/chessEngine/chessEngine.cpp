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
		case 'l':
		{
			msg.erase(0, 2);
			Position pos(msg);
			if (g.getPieceMoves(pos.xyz.x, pos.xyz.y, pos.xyz.z)[0] == '0' ||
				g.getPieceMoves(pos.xyz.x, pos.xyz.y, pos.xyz.z)[0] == '1' ||
				g.getPieceMoves(pos.xyz.x, pos.xyz.y, pos.xyz.z)[0] == '2' ||
				g.getPieceMoves(pos.xyz.x, pos.xyz.y, pos.xyz.z)[0] == '3' ||
				g.getPieceMoves(pos.xyz.x, pos.xyz.y, pos.xyz.z)[0] == '4') {
				s.sendMSG(g.colourToMove, std::string("l:") + listToAlg(g.getPieceMoves(pos.xyz.x, pos.xyz.y, pos.xyz.z)));
			}
			else {
				s.sendMSG(g.colourToMove, "l:;");
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
			if (move[0] == 'P') {
				std::string temps = "";
				for (int i = 1; i < 3; i++) {
					temps += move[i];
				}
				s.sendMSG(0, msgCopy);
				s.sendMSG(1, msgCopy);
				s.sendMSG((g.colourToMove-1)*-1, temps);
				break;
			}
			if (move[0] == 'D') {
				s.sendMSG(0, msgCopy);
				s.sendMSG(1, msgCopy);
				s.sendMSG(0, g.colourToMove == 1 ? "t:w;" : "t:b;");
				s.sendMSG(1, g.colourToMove == 1 ? "t:w;" : "t:b;");
				s.sendMSG(0, "v:d;");
				s.sendMSG(1, "v:d;");
			}
			if (move[0] == 'V') {
				s.sendMSG(0, msgCopy);
				s.sendMSG(1, msgCopy);
				s.sendMSG(0, g.colourToMove == 1 ? "t:w;" : "t:b;");
				s.sendMSG(1, g.colourToMove == 1 ? "t:w;" : "t:b;");
				if (move[1] == 'W') {
					s.sendMSG(0, "v:w;");
					s.sendMSG(1, "v:w;");
				} else {
					s.sendMSG(0, "v:b;");
					s.sendMSG(1, "v:b;");
				}
				break;
			}
			if (move[0] == 'Y' && move[4] == 'm') {
				s.sendMSG(0, msgCopy);
				s.sendMSG(1, msgCopy);

				s.sendMSG(0, g.colourToMove == 1 ? "t:w;" : "t:b;");
				s.sendMSG(1, g.colourToMove == 1 ? "t:w;" : "t:b;");
			}
		}
			break;

		case 'p':
			if(g.promotionStage) {
				std::string tempp = "";
				for (int i = 3; i < 5; i++) {
					tempp += msg[i];
				}
				Position p(tempp);
				switch (msg[2]) {
				case 'n':
					g.setPieceId(p.xyz.x, p.xyz.y, p.xyz.z, 2);
					break;
				case 'b':
					g.setPieceId(p.xyz.x, p.xyz.y, p.xyz.z, 3);
					break;
				case 'r':
					g.setPieceId(p.xyz.x, p.xyz.y, p.xyz.z, 4);
					break;
				case 'u':
					g.setPieceId(p.xyz.x, p.xyz.y, p.xyz.z, 5);
					break;
				case 'q':
					g.setPieceId(p.xyz.x, p.xyz.y, p.xyz.z, 6);
					break;
				}
				s.sendMSG(0, msg);
				s.sendMSG(1, msg);

				s.sendMSG(0, g.colourToMove == 1 ? "t:w;" : "t:b;");
				s.sendMSG(1, g.colourToMove == 1 ? "t:w;" : "t:b;");
				g.promotionStage = false;
			}
			break;
		}
	}
}