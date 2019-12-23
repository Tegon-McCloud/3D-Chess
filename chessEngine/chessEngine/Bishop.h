#pragma once
#include "Piece.h"

class Bishop : public Piece {
public:
	Bishop();
	std::string GetSymbol(const Piece& p) override;
};