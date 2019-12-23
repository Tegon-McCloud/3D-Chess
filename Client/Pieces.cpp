#include "Pieces.h"
#include "Chess.h"

std::unordered_map< std::string, std::shared_ptr<Model> > Piece::models = std::unordered_map< std::string, std::shared_ptr<Model> >();

Piece::Piece( const std::string& piece, Side s ) {
	side = s;
	
	auto key = piece + (side == WHITE ? "W" : "B");

	if ( models.find( key ) == models.end() ) {
		models[key] = std::make_shared<Model>( piece, side == WHITE ? mtlWhite : mtlBlack );
	}
	pModel = models[key];
}

void Piece::Draw( float x, float y, float z) {
	using namespace DirectX;

	if ( side == WHITE ) {
		pModel->Draw( XMMatrixTranslation( x, y, z ) );
	} else {
		pModel->Draw( XMMatrixScaling( -1.0f, 1.0f, -1.0f ) * XMMatrixTranslation( x, y, z ) );
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
