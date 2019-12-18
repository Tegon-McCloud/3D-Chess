#pragma once
#include "Model.h"

typedef enum {
	WHITE, BLACK
} Side;

class Piece : public Model {

public:
	Piece( std::string piece, Side s );

	virtual char GetSymbol() = 0;
};

class Pawn : public Piece {

public:
	Pawn( Side s );
	char GetSymbol() override;
	
};

