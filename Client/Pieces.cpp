#include "Pieces.h"

constexpr const Material mtlWhite = {
	{					// ambient:
		0.2f				// intensity
	},
	{					// diffuse:
		1.0f,				// r
		1.0f,				// g
		1.0f				// b
	},
	{					// specular:
		0.2,				// intensity
		96.0f				// shininess
	}
};

constexpr const Material mtlBlack = {
	{					// ambient:
		0.2f				// intensity
	},
	{					// diffuse:
		0.1f,				// r
		0.1f,				// g
		0.1f				// b
	},
	{					// specular:
		0.2,				// intensity
		96.0f				// shininess
	}
};

// if piece is black, flip over through x and invert polygon winding bcs we are in negative space after
Piece::Piece( std::string piece, Side s ) : Model( piece, s == WHITE ? DirectX::XMMatrixIdentity() : DirectX::XMMatrixScaling( -1.0f, 1.0f, 1.0f), s == BLACK ){
	AddBindable( std::make_shared < ConstantBuffer < Material, PS, 0u > >( s == WHITE ? &mtlWhite : &mtlBlack ) );
}

#define PIECE_IMPL( Name, Symbol ) \
Name##::##Name##( Side s ) : Piece( #Name, s ) {}\
char Name##::GetSymbol() {\
	return #@Symbol;\
}\

PIECE_IMPL( Pawn, P )
PIECE_IMPL( Rook, R );
PIECE_IMPL( Knight, N );
PIECE_IMPL( Unicorn, U );
PIECE_IMPL( Bishop, B );
PIECE_IMPL( Queen, Q );
PIECE_IMPL( King, K );
