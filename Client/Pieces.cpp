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


Piece::Piece( std::string piece, Side s ) : Model( piece ){
	AddBindable( std::make_shared < ConstantBuffer < Material, PS, 0u > >( s == WHITE ? &mtlWhite : &mtlBlack ) );
	sizeof( Material );
}

Pawn::Pawn( Side s ) : Piece( "Pawn", s ) {}

char Pawn::GetSymbol() {
	return 'P';
}
