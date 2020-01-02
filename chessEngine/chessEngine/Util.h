#pragma once
#include <string>

struct PositionLFR {
	PositionLFR(const PositionLFR& p);
	PositionLFR(int l, int f, int r);

	int l, f, r;
};

struct PositionXYZ {
	PositionXYZ(const PositionXYZ& p);
	PositionXYZ(int x, int y, int z);

	int z, x, y;
};

union Position {
	Position();
	Position(const Position& p);
	Position(const PositionLFR& p);
	Position(const PositionXYZ& p);
	Position(const std::string& alg);

	bool operator==(const Position& p);

	std::string ToAlg();

	PositionLFR lfr;
	PositionXYZ xyz;
};