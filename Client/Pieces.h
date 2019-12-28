#pragma once

#include "Model.h"

#include <unordered_map>

enum Side {
	WHITE, BLACK
};

class Piece {

public:
	Piece( const std::string& piece, Side s );

	void Draw( float x, float y, float z );

	virtual char GetSymbol() = 0;

private:
	std::shared_ptr<Model> pModel;
	Side side;

	static std::unordered_map< std::string, std::shared_ptr<Model> > models; // improve performance by only holding each model only once.
};

// macro abuse to declare a class for each piece quickly
#define PIECE_DECL( Name, Symbol ) \
class Name : public Piece {\
public:\
	Name##( Side s );\
	char GetSymbol() override;\
};

PIECE_DECL( Pawn, P );
PIECE_DECL( Rook, R );
PIECE_DECL( Knight, N );
PIECE_DECL( Unicorn, U );
PIECE_DECL( Bishop, B );
PIECE_DECL( Queen, Q );
PIECE_DECL( King, K );

#undef PIECE_DECL