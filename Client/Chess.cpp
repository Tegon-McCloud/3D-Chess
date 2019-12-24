#include "Chess.h"
#include "Pieces.h"
#include "cmath"

#include <algorithm>
#include <limits>

const std::unordered_map< char, int > alg = {	// convert from character from algebraic notation to coordinate
	{ 'A', 0 }, { 'B', 1 }, { 'C', 2 }, { 'D', 3 }, { 'E', 4 },
	{ 'a', 0 }, { 'b', 1 }, { 'c', 2 }, { 'd', 3 }, { 'e', 4 },
	{ '1', 0 }, { '2', 1 }, { '3', 2 }, { '4', 3 }, { '5', 4 },
};

// Chess
Chess::Chess() {

	player.Update( 0.0f );
	player.Bind();

	Window::Get().GetInput().RegisterRightClickListener( [ this ]( int x, int y ) -> void {

		using namespace DirectX;

		Ray r = player.LookRay();

		int lvl = -1, fl = -1 , rnk = -1;
		
		float dist = std::numeric_limits<float>::infinity();

		for ( int i = 0; i < 5; i++ ) {
			for ( int j = 0; j < 5; j++ ) {
				for ( int k = 0; k < 5; k++ ) {

					if ( pieces[i][j][k] ) {

						XMFLOAT3 boxMin;
						boxMin.x = k * 3.0f - 0.5f;
						boxMin.y = i * 6.0f - 0.0f;
						boxMin.z = j * 3.0f - 0.5f;

						XMFLOAT3 boxMax;
						boxMax.x = k * 3.0f + 0.5f;
						boxMax.y = i * 6.0f + 3.0f;
						boxMax.z = j * 3.0f + 0.5f;

						float tmin, tmax;

						// yz-plane intersection distances
						float txmin = (boxMin.x - r.ori.x) / r.dir.x;
						float txmax = (boxMax.x - r.ori.x) / r.dir.x;
						if ( txmin > txmax ) std::swap( txmin, txmax );
						
						tmin = txmin;
						tmax = txmax;
						
						float tymin = (boxMin.y - r.ori.y) / r.dir.y;
						float tymax = (boxMax.y - r.ori.y) / r.dir.y;
						if ( tymin > tymax ) std::swap( tymin, tymax );

						if ( tymax < tmin || tymin > tmax ) continue; // overshot in y direction
						
						if ( tymin > tmin ) tmin = tymin;
						if ( tymax < tmax ) tmax = tymax;

						float tzmin = (boxMin.z - r.ori.z) / r.dir.z;
						float tzmax = (boxMax.z - r.ori.z) / r.dir.z;
						if ( tzmin > tzmax ) std::swap( tzmin, tzmax );

						if ( tzmax < tmin || tzmin > tmax ) continue; // overshot in z direction

						if ( tzmin > tmin ) tmin = tzmin;
						if ( tzmax < tmax ) tmax = tzmax;


						if ( tmax < 0 ) continue;
						float t = tmin > 0.0f ? tmin : tmax;

						if ( t < dist ) {
							dist = t;
							lvl = i;
							fl = j;
							rnk = k;
						}
					}
					
				}
			}
		}
		
		printf( "%i, %i, %i\n", lvl, fl, rnk );

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
					pieces[i][j][k]->Draw( k * 3.0f, i * 6.0f, j * 3.0f );	// k(rank) -> x, i(level) -> y, j(file) -> z
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
