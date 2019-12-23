#include "Chess.h"
#include "Pieces.h"

Chess::Chess() {

	player.Update( 0.0f );
	player.Bind();

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
					pieces[i][j][k]->Draw( k * 2.5f, i * 5.0f, j * 2.5f );
				}

				board[i][j][k]->Draw( DirectX::XMMatrixTranslation( i * 2.5f, j * 5.0f, k * 2.5f ) );

			}
		}
	}
}
