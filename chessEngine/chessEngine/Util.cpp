#include "Util.h"
#include <vector>
#include <unordered_map>

std::string listToAlg(std::string list) {
	std::string algList;
	while (!list.empty()) {
		algList += Position(PositionXYZ(list[0] - '0', list[1] - '0', list[2] - '0')).ToAlg() + ",";
		list.erase(0, 4);
	}
	algList.back() = ';';
	return algList;
}

PositionLFR::PositionLFR(const PositionLFR& p) {
	l = p.l;
	f = p.f;
	r = p.r;
}

PositionLFR::PositionLFR(int l, int f, int r) : l(l), f(f), r(r) {}

PositionXYZ::PositionXYZ(const PositionXYZ& p) {
	x = p.x;
	y = p.y;
	z = p.z;
}

PositionXYZ::PositionXYZ(int x, int y, int z) : x(x), y(y), z(z) {}

Position::Position() {
	lfr.l = 0;
	lfr.f = 0;
	lfr.r = 0;
}

Position::Position(const Position& p) {
	lfr = p.lfr;
}

Position::Position(const PositionLFR& p) {
	lfr = p;
}

Position::Position(const PositionXYZ& p) {
	xyz = p;
}

Position::Position(const std::string& alg) {
	const std::unordered_map< char, int > algMap = {    // convert from character from algebraic notation to coordinate
		{ 'A', 0 }, { 'B', 1 }, { 'C', 2 }, { 'D', 3 }, { 'E', 4 },
		{ 'a', 0 }, { 'b', 1 }, { 'c', 2 }, { 'd', 3 }, { 'e', 4 },
		{ '1', 0 }, { '2', 1 }, { '3', 2 }, { '4', 3 }, { '5', 4 },
	};

	lfr.l = algMap.at(alg[0]);
	lfr.f = algMap.at(alg[1]);
	lfr.r = algMap.at(alg[2]);
}

bool Position::operator==(const Position& p) {
	return lfr.l == p.lfr.l && lfr.f == p.lfr.f && lfr.r == p.lfr.r;
}

std::string Position::ToAlg() {

	const std::vector<char> levelMap = { 'A', 'B', 'C', 'D', 'E' };
	const std::vector<char> fileMap = { 'a', 'b', 'c', 'd', 'e' };
	const std::vector<char> rankMap = { '1', '2', '3', '4', '5' };

	std::string s;
	s.push_back(levelMap[lfr.l]);
	s.push_back(fileMap[lfr.f]);
	s.push_back(rankMap[lfr.r]);

	return s;

}