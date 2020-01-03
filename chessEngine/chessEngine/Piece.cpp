#include "Piece.h"
#include <sstream>
#include <iostream>
#include "Game.h"

std::string Piece::getMoves(int colours [5][5][5], int field[5][5][5], int x, int y, int z, int colour, int type) {
	std::stringstream ss;

	switch (type) {
	//Pawn logic
	case 1:
		//TODO: perhaps fix these if statements, you could reduce them down quite a bit, atleast the conditions
		if (colour == 1) {
			//Move logic
			if (y + 1 < 5) {
				if (field[x][y + 1][z] == 0) {	//0 because if it's empty, and ids["Empty"] is 0
					ss << x << y + 1 << z << ' ';
				}
			}
			if (z + 1 < 5) {
				if (field[x][y][z + 1] == 0) {	//0 because if it's empty, and ids["Empty"] is 0
					ss << x << y << z + 1 << ' ';
				}
			}

			//Capture logic
			if (x + 1 < 5 && y + 1 < 5) {
				if (colours[x + 1][y + 1][z] == 0) {
					ss << x + 1 << y + 1 << z << ' ';
				}
			}
			if (x - 1 >= 0 && y + 1 < 5) {
				if (colours[x - 1][y + 1][z] == 0) {
					ss << x - 1 << y + 1 << z << ' ';
				}
			}
			// perhaps some logic with promotion but not here
			if (x + 1 < 5 && z + 1 < 5) {
				if (colours[x + 1][y][z + 1] == 0) {
					ss << x + 1 << y << z + 1 << ' ';
				}
			}
			if (x - 1 >= 0 && z + 1 < 5) {
				if (colours[x - 1][y][z + 1] == 0) {
					ss << x - 1 << y << z + 1 << ' ';
				}
			}
			if (y + 1 < 5 && z + 1 < 5) {
				if (colours[x][y + 1][z + 1] == 0) {
					ss << x << y + 1 << z + 1 << ' ';
				}
			}
		}
		else {
			//Move logic
			if (y - 1 >= 0) {
				if (field[x][y - 1][z] == 0) {	//0 because if it's empty, and ids["Empty"] is 0
					ss << x << y - 1 << z << ' ';
				}
			}
			if (z - 1 >= 0) {
				if (field[x][y][z - 1] == 0) {	//0 because if it's empty, and ids["Empty"] is 0
					ss << x << y << z - 1 << ' ';
				}
			}

			//Capture logic
			if (x + 1 < 5 && y - 1 >= 0) {
				if (colours[x + 1][y - 1][z] == 1) {
					ss << x + 1 << y - 1 << z << ' ';
				}
			}
			if (x - 1 >= 0 && y - 1 >= 0) {
				if (colours[x - 1][y - 1][z] == 1) {
					ss << x - 1 << y - 1 << z << ' ';
				}
			}
			// perhaps some logic with promotion but not here
			if (x + 1 < 5 && z - 1 >= 0) {
				if (colours[x + 1][y][z - 1] == 1) {
					ss << x + 1 << y << z - 1 << ' ';
				}
			}
			if (x - 1 >= 0 && z - 1 >= 0) {
				if (colours[x - 1][y][z - 1] == 1) {
					ss << x - 1 << y << z - 1 << ' ';
				}
			}
			if (y - 1 >= 0 && z - 1 >= 0) {
				if (colours[x][y - 1][z - 1] == 1) {
					ss << x << y - 1 << z - 1 << ' ';
				}
			}
		}
		return ss.str();
		break;

	//Kníght loguc
	case 2:
		//Floor 2 above the knight
		if (z + 2 < 5) {
			if (x + 1 < 5) {
				if (colours[x + 1][y][z + 2] != colour) {
					ss << x + 1 << y << z + 2 << ' ';
				}
			}
			if (x - 1 >= 0) {
				if (colours[x - 1][y][z + 2] != colour) {
					ss << x - 1 << y << z + 2 << ' ';
				}
			}
			if (y + 1 < 5) {
				if (colours[x][y + 1][z + 2] != colour) {
					ss << x << y + 1 << z + 2 << ' ';
				}
			}
			if (y - 1 >= 0) {
				if (colours[x][y - 1][z + 2] != colour) {
					ss << x << y - 1 << z + 2 << ' ';
				}
			}
		}
		//Floor 2 below the knight
		if (z - 2 >= 0) {
			if (x + 1 < 5) {
				if (colours[x + 1][y][z - 2] != colour) {
					ss << x + 1 << y << z - 2 << ' ';
				}
			}
			if (x - 1 >= 0) {
				if (colours[x - 1][y][z - 2] != colour) {
					ss << x - 1 << y << z - 2 << ' ';
				}
			}
			if (y + 1 < 5) {
				if (colours[x][y + 1][z - 2] != colour) {
					ss << x << y + 1 << z - 2 << ' ';
				}
			}
			if (y - 1 >= 0) {
				if (colours[x][y - 1][z - 2] != colour) {
					ss << x << y - 1 << z - 2 << ' ';
				}
			}
		}
		//Floor 1 above the knight
		if (z + 1 < 5) {
			if (x + 2 < 5) {
				if (colours[x + 2][y][z + 1] != colour) {
					ss << x + 2 << y << z + 1 << ' ';
				}
			}
			if (x - 2 >= 0) {
				if (colours[x - 2][y][z + 1] != colour) {
					ss << x - 2 << y << z + 1 << ' ';
				}
			}
			if (y + 2 < 5) {
				if (colours[x][y + 2][z + 1] != colour) {
					ss << x << y + 2 << z + 1 << ' ';
				}
			}
			if (y - 2 >= 0) {
				if (colours[x][y - 2][z + 1] != colour) {
					ss << x << y - 2 << z + 1 << ' ';
				}
			}
		}
		//Floor 1 below the knight
		if (z - 1 >= 0) {
			if (x + 2 < 5) {
				if (colours[x + 2][y][z - 1] != colour) {
					ss << x + 2 << y << z - 1 << ' ';
				}
			}
			if (x - 2 >= 0) {
				if (colours[x - 2][y][z - 1] != colour) {
					ss << x - 2 << y << z - 1 << ' ';
				}
			}
			if (y + 2 < 5) {
				if (colours[x][y + 2][z - 1] != colour) {
					ss << x << y + 2 << z - 1 << ' ';
				}
			}
			if (y - 2 >= 0) {
				if (colours[x][y - 2][z - 1] != colour) {
					ss << x << y - 2 << z - 1 << ' ';
				}
			}
		}
		//Same floor as knight
		if (x + 2 < 5) {
			if (y + 1 < 5) {
				if (colours[x + 2][y + 1][z] != colour) {
					ss << x + 2 << y + 1 << z << ' ';
				}
			}
			if (y - 1 >= 0) {
				if (colours[x + 2][y - 1][z] != colour) {
					ss << x + 2 << y - 1 << z << ' ';
				}
			}
		}
		if (x - 2 >= 0) {
			if (y + 1 < 5) {
				if (colours[x - 2][y + 1][z] != colour) {
					ss << x - 2 << y + 1 << z << ' ';
				}
			}
			if (y - 1 >= 0) {
				if (colours[x - 2][y - 1][z] != colour) {
					ss << x - 2 << y - 1 << z << ' ';
				}
			}
		}
		if (x + 1 < 5) {
			if (y + 2 < 5) {
				if (colours[x + 1][y + 2][z] != colour) {
					ss << x + 1 << y + 2 << z << ' ';
				}
			}
			if (y - 2 >= 0) {
				if (colours[x + 1][y - 2][z] != colour) {
					ss << x + 1 << y - 2 << z << ' ';
				}
			}
		}
		if (x - 1 >= 0) {
			if (y + 2 < 5) {
				if (colours[x - 1][y + 2][z] != colour) {
					ss << x - 1 << y + 2 << z << ' ';
				}
			}
			if (y - 2 >= 0) {
				if (colours[x - 1][y - 2][z] != colour) {
					ss << x - 1 << y - 2 << z << ' ';
				}
			}
		}
		return ss.str();
		break;

	//Bishop logic
	case 3:
		return getBishopMoves(colours, field, x, y, z, colour);
		break;

	//Rook logic
	case 4:
		return getRookMoves(colours, field, x, y, z, colour);
		break;

	//Unicorn logic
	case 5:
		return getUnicornMoves(colours, field, x, y, z, colour);
		break;

	//Queen logic
	case 6:
		ss << getBishopMoves(colours, field, x, y, z, colour) << getRookMoves(colours, field, x, y, z, colour) << getUnicornMoves(colours, field, x, y, z, colour);
		return ss.str();
		break;

	//King logic
	case 7:
		//Floor 1 above the king
		if (z + 1 < 5) {
			if (colours[x][y][z + 1] != colour) {
				ss << x << y << z + 1 << ' ';
			}
			if (y + 1 < 5) {
				if (colours[x][y + 1][z + 1] != colour) {
					ss << x << y + 1 << z + 1 << ' ';
				}
			}
			if (y - 1 >= 0) {
				if (colours[x][y - 1][z + 1] != colour) {
					ss << x << y - 1 << z + 1 << ' ';
				}
			}
			if (x + 1 < 5) {
				if (colours[x + 1][y][z + 1] != colour) {
					ss << x + 1 << y << z + 1 << ' ';
				}
				if (y + 1 < 5) {
					if (colours[x + 1][y + 1][z + 1] != colour) {
						ss << x + 1 << y + 1 << z + 1 << ' ';
					}
				}
				if (y - 1 >= 0) {
					if (colours[x + 1][y - 1][z + 1] != colour) {
						ss << x + 1 << y - 1 << z + 1 << ' ';
					}
				}
			}
			if (x - 1 >= 0) {
				if (colours[x - 1][y][z + 1] != colour) {
					ss << x - 1 << y << z + 1 << ' ';
				}
				if (y + 1 < 5) {
					if (colours[x - 1][y + 1][z + 1] != colour) {
						ss << x - 1 << y + 1 << z + 1 << ' ';
					}
				}
				if (y - 1 >= 0) {
					if (colours[x - 1][y - 1][z + 1] != colour) {
						ss << x - 1 << y - 1 << z + 1 << ' ';
					}
				}
			}
		}
		//Floor 1 below the king
		if (z - 1 >= 0) {
			if (colours[x][y][z - 1] != colour) {
				ss << x << y << z - 1 << ' ';
			}
			if (y + 1 < 5) {
				if (colours[x][y + 1][z - 1] != colour) {
					ss << x << y + 1 << z - 1 << ' ';
				}
			}
			if (y - 1 >= 0) {
				if (colours[x][y - 1][z - 1] != colour) {
					ss << x << y - 1 << z - 1 << ' ';
				}
			}
			if (x + 1 < 5) {
				if (colours[x + 1][y][z - 1] != colour) {
					ss << x + 1 << y << z - 1 << ' ';
				}
				if (y + 1 < 5) {
					if (colours[x + 1][y + 1][z - 1] != colour) {
						ss << x + 1 << y + 1 << z - 1 << ' ';
					}
				}
				if (y - 1 >= 0) {
					if (colours[x + 1][y - 1][z - 1] != colour) {
						ss << x + 1 << y - 1 << z - 1 << ' ';
					}
				}
			}
			if (x - 1 >= 0) {
				if (colours[x - 1][y][z - 1] != colour) {
					ss << x - 1 << y << z - 1 << ' ';
				}
				if (y + 1 < 5) {
					if (colours[x - 1][y + 1][z - 1] != colour) {
						ss << x - 1 << y + 1 << z - 1 << ' ';
					}
				}
				if (y - 1 >= 0) {
					if (colours[x - 1][y - 1][z - 1] != colour) {
						ss << x - 1 << y - 1 << z - 1 << ' ';
					}
				}
			}
		}
		//Same floor as king
		if (y + 1 < 5) {
			if (colours[x][y + 1][z] != colour) {
				ss << x << y + 1 << z << ' ';
			}
		}
		if (y - 1 >= 0) {
			if (colours[x][y - 1][z] != colour) {
				ss << x << y - 1 << z << ' ';
			}
		}
		if (x + 1 < 5) {
			if (colours[x + 1][y][z] != colour) {
				ss << x + 1 << y << z << ' ';
			}
			if (y + 1 < 5) {
				if (colours[x + 1][y + 1][z] != colour) {
					ss << x + 1 << y + 1 << z << ' ';
				}
			}
			if (y - 1 >= 0) {
				if (colours[x + 1][y - 1][z] != colour) {
					ss << x + 1 << y - 1 << z << ' ';
				}
			}
		}
		if (x - 1 >= 0) {
			if (colours[x - 1][y][z] != colour) {
				ss << x - 1 << y << z << ' ';
			}
			if (y + 1 < 5) {
				if (colours[x - 1][y + 1][z] != colour) {
					ss << x - 1 << y + 1 << z << ' ';
				}
			}
			if (y - 1 >= 0) {
				if (colours[x - 1][y - 1][z] != colour) {
					ss << x - 1 << y - 1 << z << ' ';
				}
			}
		}
		return ss.str();
		break;
	}
	return "Wrong type of piece";
};

std::string Piece::getUnicornMoves(int colours[5][5][5], int field[5][5][5], int x, int y, int z, int colour) {
	std::stringstream ss;
	bool temp;	//temp = has it hit something
	int shortestDist;
	//x positive y positive z positive dir
	temp = true;
	if ((4 - x <= 4 - y) && (4 - x <= 4 - z)) {
		shortestDist = 4 - x;
	}
	else if ((4 - y <= 4 - x) && (4 - y <= 4 - z)) {
		shortestDist = 4 - y;
	}
	else {
		shortestDist = 4 - z;
	}
	for (int i = 1; i <= shortestDist && temp; i++) {
		if (colours[x + i][y + i][z + i] == colour) {
			temp = false;
		}
		else {
			if (field[x + i][y + i][z + i] == (colour - 1)*-1 && colours[x + i][y + i][z + i] != -1) {
				temp = false;
			}
			ss << x + i << y + i << z + i << ' ';
		}
	}
	//x positive y positive z negative dir
	temp = true;
	if ((4 - x <= 4 - y) && (4 - x <= z)) {
		shortestDist = 4 - x;
	}
	else if ((4 - y <= 4 - x) && (4 - y <= z)) {
		shortestDist = 4 - y;
	}
	else {
		shortestDist = z;
	}
	for (int i = 1; i <= shortestDist && temp; i++) {
		if (colours[x + i][y + i][z - i] == colour) {
			temp = false;
		}
		else {
			if (field[x + i][y + i][z - i] == (colour - 1)*-1 && colours[x + i][y + i][z - i] != -1) {
				temp = false;
			}
			ss << x + i << y + i << z - i << ' ';
		}
	}
	//x positive y positive z positive dir
	temp = true;
	if ((4 - x <= y) && (4 - x <= 4 - z)) {
		shortestDist = 4 - x;
	}
	else if ((y <= 4 - x) && (y <= 4 - z)) {
		shortestDist = y;
	}
	else {
		shortestDist = 4 - z;
	}
	for (int i = 1; i <= shortestDist && temp; i++) {
		if (colours[x + i][y - i][z + i] == colour) {
			temp = false;
		}
		else {
			if (field[x + i][y - i][z + i] == (colour - 1)*-1 && colours[x + i][y - i][z + i] != -1) {
				temp = false;
			}
			ss << x + i << y - i << z + i << ' ';
		}
	}
	//x positive y positive z negative dir
	temp = true;
	if ((4 - x <= y) && (4 - x <= z)) {
		shortestDist = 4 - x;
	}
	else if ((y <= 4 - x) && (y <= z)) {
		shortestDist = y;
	}
	else {
		shortestDist = z;
	}
	for (int i = 1; i <= shortestDist && temp; i++) {
		if (colours[x + i][y - i][z - i] == colour) {
			temp = false;
		}
		else {
			if (field[x + i][y - i][z - i] == (colour - 1)*-1 && colours[x + i][y - i][z - i] != -1) {
				temp = false;
			}
			ss << x + i << y - i << z - i << ' ';
		}
	}
	//x positive y positive z positive dir
	temp = true;
	if ((x <= 4 - y) && (x <= 4 - z)) {
		shortestDist = x;
	}
	else if ((4 - y <= x) && (4 - y <= 4 - z)) {
		shortestDist = 4 - y;
	}
	else {
		shortestDist = 4 - z;
	}
	for (int i = 1; i <= shortestDist && temp; i++) {
		if (colours[x - i][y + i][z + i] == colour) {
			temp = false;
		}
		else {
			if (field[x - i][y + i][z + i] == (colour - 1)*-1 && colours[x - i][y + i][z + i] != -1) {
				temp = false;
			}
			ss << x - i << y + i << z + i << ' ';
		}
	}
	//x positive y positive z negative dir
	temp = true;
	if ((x <= 4 - y) && (x <= z)) {
		shortestDist = x;
	}
	else if ((4 - y <= x) && (4 - y <= z)) {
		shortestDist = 4 - y;
	}
	else {
		shortestDist = z;
	}
	for (int i = 1; i <= shortestDist && temp; i++) {
		if (colours[x - i][y + i][z - i] == colour) {
			temp = false;
		}
		else {
			if (field[x - i][y + i][z - i] == (colour - 1)*-1 && colours[x - i][y + i][z - i] != -1) {
				temp = false;
			}
			ss << x - i << y + i << z - i << ' ';
		}
	}
	//x positive y positive z positive dir
	temp = true;
	if ((x <= y) && (x <= 4 - z)) {
		shortestDist = x;
	}
	else if ((y <= x) && (y <= 4 - z)) {
		shortestDist = y;
	}
	else {
		shortestDist = 4 - z;
	}
	for (int i = 1; i <= shortestDist && temp; i++) {
		if (colours[x - i][y - i][z + i] == colour) {
			temp = false;
		}
		else {
			if (field[x - i][y - i][z + i] == (colour - 1)*-1 && colours[x - i][y - i][z + i] != -1) {
				temp = false;
			}
			ss << x - i << y - i << z + i << ' ';
		}
	}
	//x positive y positive z negative dir
	temp = true;
	if ((x <= y) && (x <= z)) {
		shortestDist = x;
	}
	else if ((y <= x) && (y <= z)) {
		shortestDist = y;
	}
	else {
		shortestDist = z;
	}
	for (int i = 1; i <= shortestDist && temp; i++) {
		if (colours[x - i][y - i][z - i] == colour) {
			temp = false;
		}
		else {
			if (field[x - i][y - i][z - i] == (colour - 1)*-1 && colours[x - i][y - i][z - i] != -1) {
				temp = false;
			}
			ss << x - i << y - i << z - i << ' ';
		}
	}
	return ss.str();
}

std::string Piece::getRookMoves(int colours[5][5][5], int field[5][5][5], int x, int y, int z, int colour) {
	std::stringstream ss;
	bool temp;	//temp = has it hit something
	int shortestDist;
	//x positive dir
	temp = true;
	shortestDist = 4 - x;
	for (int i = 1; i <= shortestDist && temp; i++) {
		if (colours[x + i][y][z] == colour) {
			temp = false;
		}
		else {
			if (field[x + i][y][z] == (colour - 1)*-1 && colours[x + i][y][z] != -1) {
				temp = false;
			}
			ss << x + i << y << z << ' ';
		}
	}
	//x negative dir
	temp = true;
	shortestDist = x;
	for (int i = 1; i <= shortestDist && temp; i++) {
		if (colours[x - i][y][z] == colour) {
			temp = false;
		}
		else {
			if (field[x - i][y][z] == (colour - 1)*-1 && colours[x - i][y][z] != -1) {
				temp = false;
			}
			ss << x - i << y << z << ' ';
		}
	}
	//y positive dir
	temp = true;
	shortestDist = 4 - y;
	for (int i = 1; i <= shortestDist && temp; i++) {
		if (colours[x][y + i][z] == colour) {
			temp = false;
		}
		else {
			if (field[x][y + i][z] == (colour - 1)*-1 && colours[x][y + i][z] != -1) {
				temp = false;
			}
			ss << x << y + i << z << ' ';
		}
	}
	//y negative dir
	temp = true;
	shortestDist = y;
	for (int i = 1; i <= shortestDist && temp; i++) {
		if (colours[x][y - i][z] == colour) {
			temp = false;
		}
		else {
			if (field[x][y - i][z] == (colour - 1)*-1 && colours[x][y - i][z] != -1) {
				temp = false;
			}
			ss << x << y - i << z << ' ';
		}
	}
	//z positive dir
	temp = true;
	shortestDist = 4 - z;
	for (int i = 1; i <= shortestDist && temp; i++) {
		if (colours[x][y][z + i] == colour) {
			temp = false;
		}
		else {
			if (field[x][y][z + i] == (colour - 1)*-1 && colours[x][y][z + i] != -1) {
				temp = false;
			}
			ss << x << y << z + i << ' ';
		}
	}
	//z negative dir
	temp = true;
	shortestDist = z;
	for (int i = 1; i <= shortestDist && temp; i++) {
		if (colours[x][y][z - i] == colour) {
			temp = false;
		}
		else {
			if (field[x][y][z - i] == (colour - 1)*-1 && colours[x][y][z - i] != -1) {
				temp = false;
			}
			ss << x << y << z - i << ' ';
		}
	}
	return ss.str();
}

std::string Piece::getBishopMoves(int colours[5][5][5], int field[5][5][5], int x, int y, int z, int colour) {
	std::stringstream ss;
	bool temp;	//temp = has it hit something
	int shortestDist;
	//xy-plane
	//x positive y positive dir
	temp = true;
	if (4 - x >= 4 - y) {
		 shortestDist = 4 - y;
	}
	else {
		shortestDist = 4 - x;
	}
	for (int i = 1; i <= shortestDist && temp; i++) {
		if (colours[x + i][y + i][z] == colour) {
			temp = false;
		}
		else {
			if (colours[x + i][y + i][z] == (colour - 1)*-1 && colours[x + i][y + i][z] != -1) {
				temp = false;
			}
			ss << x + i << y + i << z << ' ';
		}
	}
	temp = true;
	//x positive y negative dir
	if (4 - x >= y) {
		shortestDist = y;
	}
	else {
		shortestDist = 4 - x;
	}
	for (int i = 1; i <= shortestDist && temp; i++) {
		if (colours[x + i][y - i][z] == colour) {
			temp = false;
		}
		else {
			if (colours[x + i][y - i][z] == (colour - 1)*-1 && colours[x + i][y - i][z] != -1) {
				temp = false;
			}
			ss << x + i << y - i << z << ' ';
		}
	}
	//x negative y positive dir
	temp = true;
	if (x <= 4 - y) {
		shortestDist = x;
	}
	else {
		shortestDist = 4 - y;
	}
	for (int i = 1; i <= shortestDist && temp; i++) {
		if (colours[x - i][y + i][z] == colour) {
			temp = false;
		}
		else {
			if (colours[x - i][y + i][z] == (colour - 1)*-1 && colours[x - i][y + i][z] != -1) {
				temp = false;
			}
			ss << x - i << y + i << z << ' ';
		}
	}
	//x negative y negative dir
	temp = true;
	if (x <= y) {
		shortestDist = x;
	}
	else {
		shortestDist = y;
	}
	for (int i = 1; i <= shortestDist && temp; i++) {
		if (colours[x - i][y - i][z] == colour) {
			temp = false;
		}
		else {
			if (colours[x - i][y - i][z] == (colour - 1)*-1 && colours[x - i][y - i][z] != -1) {
				temp = false;
			}
			ss << x - i << y - i << z << ' ';
		}
	}
	//xz-plane
	//x positive z positive dir
	temp = true;
	if (4 - x <= 4 - z) {
		shortestDist = 4 - x;
	}
	else {
		shortestDist = 4 - z;
	}
	for (int i = 1; i <= shortestDist && temp; i++) {
		if (colours[x + i][y][z + i] == colour) {
			temp = false;
		}
		else {
			if (colours[x + i][y][z + i] == (colour - 1)*-1 && colours[x + i][y][z + i] != -1) {
				temp = false;
			}
			ss << x + i << y << z + i << ' ';
		}
	}
	//x positive z negative dir
	temp = true;
	if (4 - x <= z) {
		shortestDist = 4 - x;
	}
	else {
		shortestDist = z;
	}
	for (int i = 1; i <= shortestDist && temp; i++) {
		if (colours[x + i][y][z - i] == colour) {
			temp = false;
		}
		else {
			if (colours[x + i][y][z - i] == (colour - 1)*-1 && colours[x + i][y][z - i] != -1) {
				temp = false;
			}
			ss << x + i << y << z - i << ' ';
		}
	}
	//x negative z positive dir
	temp = true;
	if (x <= 4 - z) {
		shortestDist = x;
	}
	else {
		shortestDist = 4 - z;
	}
	for (int i = 1; i <= shortestDist && temp; i++) {
		if (colours[x - i][y][z + i] == colour) {
			temp = false;
		}
		else {
			if (colours[x - i][y][z + i] == (colour - 1)*-1 && colours[x - i][y][z + i] != -1) {
				temp = false;
			}
			ss << x - i << y << z + i << ' ';
		}
	}
	//x negative z negative dir
	temp = true;
	if (x <= z) {
		shortestDist = x;
	}
	else {
		shortestDist = z;
	}
	for (int i = 1; i <= shortestDist && temp; i++) {
		if (colours[x - i][y][z - i] == colour) {
			temp = false;
		}
		else {
			if (colours[x - i][y][z - i] == (colour - 1)*-1 && colours[x - i][y][z - i] != -1) {
				temp = false;
			}
			ss << x - i << y << z - i << ' ';
		}
	}
	//yz-plane
	//y positive z positive dir
	temp = true;
	if (4 - y <= 4 - z) {
		shortestDist = 4 - y;
	}
	else {
		shortestDist = 4 - z;
	}
	for (int i = 1; i <= shortestDist && temp; i++) {
		if (colours[x][y + i][z + i] == colour) {
			temp = false;
		}
		else {
			if (colours[x][y + i][z + i] == (colour - 1)*-1 && colours[x][y + i][z + i] != -1) {
				temp = false;
			}
			ss << x << y + i << z + i << ' ';
		}
	}
	//y positive z negative dir
	temp = true;
	if (4 - y <= z) {
		shortestDist = 4 - y;
	}
	else {
		shortestDist = z;
	}
	for (int i = 1; i <= shortestDist && temp; i++) {
		if (colours[x][y + i][z - i] == colour) {
			temp = false;
		}
		else {
			if (colours[x][y + i][z - i] == (colour - 1)*-1 && colours[x][y + i][z - i] != -1) {
				temp = false;
			}
			ss << x << y + i << z - i << ' ';
		}
	}
	//y negative z positive dir
	temp = true;
	if (y <= 4 - z) {
		shortestDist = y;
	}
	else {
		shortestDist = 4 - z;
	}
	for (int i = 1; i <= shortestDist && temp; i++) {
		if (colours[x][y - i][z + i] == colour) {
			temp = false;
		}
		else {
			if (colours[x][y - i][z + i] == (colour - 1)*-1 && colours[x][y - i][z + i] != -1) {
				temp = false;
			}
			ss << x << y - i << z + i << ' ';
		}
	}
	//y negative z negative dir
	temp = true;
	if (y <= z) {
		shortestDist = y;
	}
	else {
		shortestDist = z;
	}
	for (int i = 1; i <= shortestDist && temp; i++) {
		if (colours[x][y - i][z - i] == colour) {
			temp = false;
		}
		else {
			if (colours[x][y - i][z - i] == (colour - 1)*-1 && colours[x][y - i][z - i] != -1) {
				temp = false;
			}
			ss << x << y - i << z - i << ' ';
		}
	}
	return ss.str();
};

void Piece::move(int colours[5][5][5], int field[5][5][5], int x, int y, int z, int colour, int type) {

};

void Piece::printMoves(int colours[5][5][5], int field[5][5][5], int x, int y, int z, int colour, int type) {
	std::cout << getMoves(colours, field, x, y, z, colour, type);
};