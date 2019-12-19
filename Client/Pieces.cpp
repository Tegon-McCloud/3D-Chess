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
		0.1,				// intensity
		24.0f				// shininess
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
		0.1,				// intensity
		24.0f				// shininess
	}
};

Piece::Piece( const std::string& piece, Side s ) : Model( piece, s == WHITE ? mtlWhite : mtlBlack ) {
	this->s = s;
}

void Piece::Draw( int level, int file, int rank ) {
	using namespace DirectX;

	if ( s == WHITE ) {
		Model::Draw( XMMatrixTranslation( rank * 1.0f, level * 1.0f, file * 1.0f ) );
	} else {
		Model::Draw( XMMatrixScaling( -1.0f, 1.0f, -1.0f ) * XMMatrixTranslation( rank * 1.0f, level * 1.0f, file * 1.0f ) );
	}


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
