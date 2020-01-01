#include "Piece.h"

#include <typeinfo>
#include <typeindex>

constexpr const Material mtlWhitePiece = {
	{					// color
		1.0f,				// r
		1.0f,				// g
		1.0f				// b
	},
	{					// ambient:
		0.2f				// intensity
	},
	{					// diffuse:
		1.0f				// intensity
	},
	{					// specular:
		0.1,				// intensity
		24.0f				// shininess
	},
	0.0f				// transparency
};

constexpr const Material mtlBlackPiece = {
	{					// color
		0.1f,				// r
		0.1f,				// g
		0.1f				// b
	},
	{					// ambient:
		0.2f				// intensity
	},
	{					// diffuse:
		1.0f				// intensity
	},
	{					// specular:
		0.1,				// intensity
		24.0f				// shininess
	},
	0.0f				// transparency
};

std::unordered_map< std::string, std::shared_ptr<Model> > Piece::models = std::unordered_map< std::string, std::shared_ptr<Model> >();

const std::unordered_map<std::string, PieceInfo> pieceInfo( {
	{ "Pawn",		{ 'P', 1.00f, 2.07f } },	// symbol, diameter, height
	{ "Rook",		{ 'R', 1.30f, 2.38f } },
	{ "Knight",		{ 'N', 1.15f, 2.74f } },
	{ "Unicorn",	{ 'U', 1.15f, 2.74f } },
	{ "Bishop",		{ 'B', 1.18f, 3.60f } },
	{ "Queen",		{ 'Q', 1.18f, 4.31f } },
	{ "King",		{ 'K', 1.18f, 4.86f } }
} );

Piece::Piece( const std::string& piece, Side s ) {

	side = s;
	
	auto key = piece + (side == WHITE ? "W" : "B");

	if ( models.find( key ) == models.end() ) {
		models[key] = std::make_shared<Model>( piece, side == WHITE ? mtlWhitePiece : mtlBlackPiece );
	}
	pModel = models[key];

	info = pieceInfo.at( piece );
}

void Piece::Draw( float x, float y, float z) {
	using namespace DirectX;

	if ( side == WHITE ) {
		pModel->Draw( XMMatrixTranslation( x, y, z ) );
	} else {
		pModel->Draw( XMMatrixScaling( -1.0f, 1.0f, -1.0f ) * XMMatrixTranslation( x, y, z ) );
	}
}

const PieceInfo& Piece::GetInfo() {
	return info;
}

