#include "Chess.h"
#include "Pieces.h"

const std::unordered_map< char, int > alg = {
	{ 'A', 0 }, { 'B', 1 }, { 'C', 2 }, { 'D', 3 }, { 'E', 4 },
	{ 'a', 0 }, { 'b', 1 }, { 'c', 2 }, { 'd', 3 }, { 'e', 4 },
	{ '1', 0 }, { '2', 1 }, { '3', 2 }, { '4', 3 }, { '5', 4 },
};

// Chess
Chess::Chess() {

	player.Update( 0.0f );
	player.Bind();

	Window::Get().GetInput().RegisterRightClickListener( [ this ]( int x, int y ) -> void {
		MovePiece( "Aa1", "Aa3" );
	} );

	light.rgb = { 1.0f, 1.0f, 1.0f };
	light.dir = { 0.0f, -1.0f, 0.0f };
	lightBuffer.Set( &light );
	lightBuffer.Bind();

	// board setup
	auto whiteSquare = std::make_shared< Model >( "Square", mtlWhite );
	auto blackSquare = std::make_shared< Model >( "Square", mtlBlack );
	
	for ( int i = 0; i < 5; i++ ) {
		for ( int j = 0; j < 5; j++ ) {
			for ( int k = 0; k < 5; k++ ) {
				
				// Pawns
				if ( k == 1 && i < 2) {
					pieces[i][j][k].reset(new Pawn( WHITE ));
				}

				if ( k == 3 && i > 2 ) {
					pieces[i][j][k].reset(new Pawn( BLACK ));
				}

				// Board
				board[i][j][k] = (i + j + k) % 2 == 0 ? whiteSquare : blackSquare;
				
			}
		}
	}

	pieces[0][0][0].reset( new Rook( WHITE ) );
	pieces[0][1][0].reset( new Knight( WHITE ) );
	pieces[0][2][0].reset( new King( WHITE ) );
	pieces[0][3][0].reset( new Knight( WHITE ) );
	pieces[0][4][0].reset( new Rook( WHITE ) );
	
	pieces[1][0][0].reset( new Bishop( WHITE ) );
	pieces[1][1][0].reset( new Unicorn( WHITE ) );
	pieces[1][2][0].reset( new Queen( WHITE ) );
	pieces[1][3][0].reset( new Bishop( WHITE ) );
	pieces[1][4][0].reset( new Unicorn( WHITE ) );

	pieces[4][0][4].reset( new Rook( BLACK ) );
	pieces[4][1][4].reset( new Knight( BLACK ) );
	pieces[4][2][4].reset( new King( BLACK ) );
	pieces[4][3][4].reset( new Knight( BLACK ) );
	pieces[4][4][4].reset( new Rook( BLACK ) );

	pieces[3][0][4].reset( new Unicorn( BLACK ) );
	pieces[3][1][4].reset( new Bishop( BLACK ) );
	pieces[3][2][4].reset( new Queen( BLACK ) );
	pieces[3][3][4].reset( new Unicorn( BLACK ) );
	pieces[3][4][4].reset( new Bishop( BLACK ) );
}

void Chess::Update( float dt ) {
	player.Update( dt );
}

void Chess::Draw() {
	using namespace DirectX;

	const XMVECTOR lightDirWorld = XMVector3Normalize( { 1.0f, -1.0f, 1.0f, 0.0f } );
	XMVECTOR lightDirView = player.ToViewSpace4( lightDirWorld );

	XMStoreFloat3( &light.dir, lightDirView );

	lightBuffer.Set( &light );

	for ( int i = 0; i < 5; i++ ) {
		for ( int j = 0; j < 5; j++ ) {
			for ( int k = 0; k < 5; k++ ) {

				if ( pieces[i][j][k] ) {
					pieces[i][j][k]->Draw( k * 3.0f, i * 6.0f, j * 3.0f );	// rank -> x, level -> y, file -> z
				}

				board[i][j][k]->Draw( DirectX::XMMatrixTranslation( k * 3.0f, i * 6.0f, j * 3.0f ) );
			}
		}
	}
}

void Chess::MovePiece( std::string from, std::string to ) {
	CellAt( to ) = std::move( CellAt( from ) );
}

Piece& Chess::PieceAt( std::string pos ) {
	return *CellAt( pos );
}

std::shared_ptr<Piece>& Chess::CellAt( std::string pos ) {
	return pieces[alg.at( pos[0] )][alg.at( pos[1] )][alg.at( pos[2] )];
}
