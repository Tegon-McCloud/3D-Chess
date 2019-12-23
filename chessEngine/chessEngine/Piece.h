#pragma once

#include <typeinfo>
#include <string>

class Piece {
public:
	//static int idOf(const Piece& p);
	virtual std::string GetSymbol(const Piece& p) = 0;
private:
};