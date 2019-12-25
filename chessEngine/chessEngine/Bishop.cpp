#include "Bishop.h"
#include <sstream>
#include <iostream>

std::string Bishop::getMoves(int* colours [5][5][5], int* field[5][5][5], int x, int y, int z, int colour) {
	std::stringstream ss;
	int shortestDist;

	//xy-plane
	//x positive y positive dir
	bool temp1 = true;	//temp = has it hit something
	if (4 - x >= 4 - y) {
		shortestDist = 4 - x;
	} else {
		shortestDist = 4 - y;
	}
	for (int i = 1; i <= shortestDist && temp1; i++) {
		if (*colours[x+i][y+i][z] == colour) {
			temp1 = false;
		}
		else {
			if (*field[x+i][y+i][z] == (colour - 1)*-1) {
			temp1 = false;
			}
			ss << x+i << y+i << z << ' ';
		}
	}

	//x positive y negative dir
	bool temp2 = true;
	if (4 - x >= y) {
		shortestDist = 4 - x;
	}
	else {
		shortestDist = y;
	}
	for (int i = 1; i <= shortestDist && temp2; i++) {
		if (*colours[x + i][y - i][z] == colour) {
			temp2 = false;
		}
		else {
			if (*field[x + i][y - i][z] == (colour - 1)*-1) {
				temp2 = false;
			}
			ss << x + i << y - i << z << ' ';
		}
	}

	//x negative y positive dir
	bool temp3 = true;
	if (x >= 4 - y) {
		shortestDist = x;
	}
	else {
		shortestDist = 4 - y;
	}
	for (int i = 1; i <= shortestDist && temp3; i++) {
		if (*colours[x - i][y + i][z] == colour) {
			temp3 = false;
		}
		else {
			if (*field[x - i][y + i][z] == (colour - 1)*-1) {
				temp3 = false;
			}
			ss << x - i << y + i << z << ' ';
		}
	}

	//x negative y negative dir
	bool temp4 = true;
	if (x >= y) {
		shortestDist = x;
	}
	else {
		shortestDist = y;
	}
	for (int i = 1; i <= shortestDist && temp4; i++) {
		if (*colours[x - i][y - i][z] == colour) {
			temp4 = false;
		}
		else {
			if (*field[x - i][y - i][z] == (colour - 1)*-1) {
				temp4 = false;
			}
			ss << x - i << y - i << z << ' ';
		}
	}

	//xz-plane
	//x positive z positive dir
	bool temp5 = true;
	if (4 - x >= 4 - z) {
		shortestDist = 4 - x;
	}
	else {
		shortestDist = 4 - z;
	}
	for (int i = 1; i <= shortestDist && temp5; i++) {
		if (*colours[x + i][y][z + i] == colour) {
			temp5 = false;
		}
		else {
			if (*field[x + i][y][z + i] == (colour - 1)*-1) {
				temp5 = false;
			}
			ss << x + i << y << z + i << ' ';
		}
	}

	//x positive z negative dir
	bool temp6 = true;
	if (4 - x >= z) {
		shortestDist = 4 - x;
	}
	else {
		shortestDist = z;
	}
	for (int i = 1; i <= shortestDist && temp6; i++) {
		if (*colours[x + i][y][z - i] == colour) {
			temp6 = false;
		}
		else {
			if (*field[x + i][y][z - 1] == (colour - 1)*-1) {
				temp6 = false;
			}
			ss << x + i << y << z - 1 << ' ';
		}
	}

	//x negative z positive dir
	bool temp7 = true;
	if (x >= 4 - z) {
		shortestDist = x;
	}
	else {
		shortestDist = 4 - z;
	}
	for (int i = 1; i <= shortestDist && temp7; i++) {
		if (*colours[x - i][y][z + i] == colour) {
			temp7 = false;
		}
		else {
			if (*field[x - i][y][z + i] == (colour - 1)*-1) {
				temp7 = false;
			}
			ss << x - i << y << z + i << ' ';
		}
	}

	//x negative z negative dir
	bool temp8 = true;
	if (x >= z) {
		shortestDist = x;
	}
	else {
		shortestDist = z;
	}
	for (int i = 1; i <= shortestDist && temp8; i++) {
		if (*colours[x - i][y][z - i] == colour) {
			temp8 = false;
		}
		else {
			if (*field[x - i][y][z - i] == (colour - 1)*-1) {
				temp8 = false;
			}
			ss << x - i << y << z - i << ' ';
		}
	}

	//yz-plane
	//y positive z positive dir
	bool temp9 = true;
	if (4 - y >= 4 - z) {
		shortestDist = 4 - y;
	}
	else {
		shortestDist = 4 - z;
	}
	for (int i = 1; i <= shortestDist && temp9; i++) {
		if (*colours[x][y + i][z + i] == colour) {
			temp9 = false;
		}
		else {
			if (*field[x][y + i][z + i] == (colour - 1)*-1) {
				temp9 = false;
			}
			ss << x << y + i << z + i << ' ';
		}
	}

	//y positive z negative dir
	bool temp10 = true;
	if (4 - y >= z) {
		shortestDist = 4 - y;
	}
	else {
		shortestDist = z;
	}
	for (int i = 1; i <= shortestDist && temp10; i++) {
		if (*colours[x][y + i][z - i] == colour) {
			temp10 = false;
		}
		else {
			if (*field[x][y + i][z - 1] == (colour - 1)*-1) {
				temp10 = false;
			}
			ss << x << y + i << z - 1 << ' ';
		}
	}

	//y negative z positive dir
	bool temp11 = true;
	if (y >= 4 - z) {
		shortestDist = y;
	}
	else {
		shortestDist = 4 - z;
	}
	for (int i = 1; i <= shortestDist && temp11; i++) {
		if (*colours[x][y - i][z + i] == colour) {
			temp11 = false;
		}
		else {
			if (*field[x][y - i][z + i] == (colour - 1)*-1) {
				temp11 = false;
			}
			ss << x << y - i << z + i << ' ';
		}
	}

	//y negative z negative dir
	bool temp12 = true;
	if (y >= z) {
		shortestDist = y;
	}
	else {
		shortestDist = z;
	}
	for (int i = 1; i <= shortestDist && temp12; i++) {
		if (*colours[x][y - i][z - i] == colour) {
			temp12 = false;
		}
		else {
			if (*field[x][y - i][z - i] == (colour - 1)*-1) {
				temp12 = false;
			}
			ss << x << y - i << z - i << ' ';
		}
	}
	return ss.str();
};

void Bishop::move(int* colours[5][5][5], int* field[5][5][5], int x, int y, int z, int colour) {

};

void Bishop::printMoves(int* colours[5][5][5], int* field[5][5][5], int x, int y, int z, int colour) {
	std::cout << getMoves(colours, field, x, y, z, colour);
};

Bishop::Bishop() {

};