#pragma once

#include "Model.h"

typedef enum {
	WHITE, BLACK
} Side;

class Piece : public Model {

public:
	Piece( const std::string& piece, Side s );

	void Draw( float x, float y, float z );

	virtual char GetSymbol() = 0;

	Side s;

};

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