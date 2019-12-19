#include "Chess.h"

Chess::Chess() {

	player.Update( 0.0f );
	player.Bind();

	for ( int i = 0; i < 5; i++ ) {
		for ( int j = 0; j < 5; j++ ) {
			for ( int k = 0; k < 5; k++ ) {
				
				if ( k == 1 && i < 2) {
					board[i][j][k].reset(new Pawn( WHITE ));
				}

				if ( k == 3 && i > 2 ) {
					board[i][j][k].reset(new Pawn( BLACK ));
				}

			}
		}
	}

	board[0][0][0].reset( new Rook( WHITE ) );
	board[0][1][0].reset( new Knight( WHITE ) );
	board[0][2][0].reset( new King( WHITE ) );
	board[0][3][0].reset( new Knight( WHITE ) );
	board[0][4][0].reset( new Rook( WHITE ) );
	
	board[1][0][0].reset( new Bishop( WHITE ) );
	board[1][1][0].reset( new Unicorn( WHITE ) );
	board[1][2][0].reset( new Queen( WHITE ) );
	board[1][3][0].reset( new Bishop( WHITE ) );
	board[1][4][0].reset( new Unicorn( WHITE ) );

	board[4][0][4].reset( new Rook( BLACK ) );
	board[4][1][4].reset( new Knight( BLACK ) );
	board[4][2][4].reset( new King( BLACK ) );
	board[4][3][4].reset( new Knight( BLACK ) );
	board[4][4][4].reset( new Rook( BLACK ) );

	board[3][0][4].reset( new Unicorn( BLACK ) );
	board[3][1][4].reset( new Bishop( BLACK ) );
	board[3][2][4].reset( new Queen( BLACK ) );
	board[3][3][4].reset( new Unicorn( BLACK ) );
	board[3][4][4].reset( new Bishop( BLACK ) );
}

void Chess::Update( float dt ) {
	player.Update( dt );
}

void Chess::Draw() {
	for ( int i = 0; i < 5; i++ ) {
		for ( int j = 0; j < 5; j++ ) {
			for ( int k = 0; k < 5; k++ ) {

				if ( board[i][j][k] ) {
					board[i][j][k]->Draw( k * 2.5f, i * 5.0f, j * 2.5f );
				}

			}
		}
	}
}
