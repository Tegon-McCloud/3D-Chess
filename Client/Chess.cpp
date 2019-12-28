#include "Chess.h"
#include "Pieces.h"
#include "Util.h"

#include <algorithm>
#include <limits>

constexpr const Material mtlWhiteSquare = {
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

constexpr const Material mtlBlackSquare = {
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

constexpr const Material mtlSelected = {
	{					// color
		0.1f,				// r
		0.5f,				// g
		0.1f				// b
	},
	{					// ambient:
		1.0f				// intensity
	},
	{					// diffuse:
		0.0f				// intensity
	},
	{					// specular:
		0.1,				// intensity
		24.0f				// shininess
	},
	0.5f				// transparency			// transparency
};

// Chess
Chess::Chess() : 
	pieces(5, std::array<std::array<std::shared_ptr<Piece>, 5>, 5>()), 
	whiteSquare( "Square", mtlWhiteSquare ), 
	blackSquare( "Square", mtlBlackSquare ),
	highlightBox( "Box", mtlSelected ) {

	player.Update( 0.0f );
	player.Bind();

	Window::Get().GetInput().RegisterClickListener( [ this ]( int x, int y ) -> void {

		using namespace DirectX;

		PositionLFR clickedPos( -1, -1, -1 );

		float dist = std::numeric_limits<float>::infinity();

		for ( int i = 0; i < 5; i++ ) {
			for ( int j = 0; j < 5; j++ ) {
				for ( int k = 0; k < 5; k++ ) {

					if ( !pieces[i][j][k] ) continue;

					PieceInfo info = pieces[i][j][k]->GetInfo();
					Box hitbox;
					hitbox.min.x = k * 3.0f - 0.5f * info.diameter;
					hitbox.min.y = i * 6.0f - 0.0f * info.height;
					hitbox.min.z = j * 3.0f - 0.5f * info.diameter;

					hitbox.max.x = k * 3.0f + 0.5f * info.diameter;
					hitbox.max.y = i * 6.0f + 1.0f * info.height;
					hitbox.max.z = j * 3.0f + 0.5f * info.diameter;

					float t = intersection( player.LookRay(), hitbox );

					if ( t < dist ) {
						dist = t;
						clickedPos.l = i;
						clickedPos.f = j;
						clickedPos.r = k;
					}
				}
			}
		}

		if ( Position( clickedPos ) == Position( PositionLFR( -1, -1, -1 ) ) ) {
			selectedPos.reset();
			return;
		};

		if ( !selectedPos ) {
			selectedPos.reset( new PositionLFR( clickedPos ) );
		} else {
			MovePiece( *selectedPos, clickedPos );
			selectedPos.reset();
		}

	} );

	light.rgb = { 1.0f, 1.0f, 1.0f };
	light.dir = { 0.0f, -1.0f, 0.0f };
	lightBuffer.Set( &light );
	lightBuffer.Bind();

	// board setup
	for ( int i = 0; i < 5; i++ ) {
		for ( int j = 0; j < 5; j++ ) {
			for ( int k = 0; k < 5; k++ ) {
				
				// Pawns
				if ( k == 1 && i < 2) {
					pieces[i][j][k].reset(new Piece( "Pawn", WHITE ));
				}

				if ( k == 3 && i > 2 ) {
					pieces[i][j][k].reset(new Piece( "Pawn", BLACK ));
				}
				
			}
		}
	}

#define SETW(l, f, r, piece) pieces[l][f][r].reset( new Piece( #piece, WHITE ) )
	
	SETW( 0, 0, 0, Rook );
	SETW( 0, 1, 0, Knight );
	SETW( 0, 2, 0, King );
	SETW( 0, 3, 0, Knight );
	SETW( 0, 4, 0, Rook );
	
	SETW( 1, 0, 0, Bishop );
	SETW( 1, 1, 0, Unicorn );
	SETW( 1, 2, 0, Queen );
	SETW( 1, 3, 0, Bishop );
	SETW( 1, 4, 0, Unicorn );

#undef SETW
#define SETB(l, f, r, piece) pieces[l][f][r].reset( new Piece( #piece, BLACK ) );
	
	SETB( 4, 0, 4, Rook );
	SETB( 4, 1, 4, Knight );
	SETB( 4, 2, 4, King );
	SETB( 4, 3, 4, Knight );
	SETB( 4, 4, 4, Rook );

	SETB( 3, 0, 4, Unicorn );
	SETB( 3, 0, 4, Bishop );
	SETB( 3, 0, 4, Queen );
	SETB( 3, 0, 4, Unicorn );
	SETB( 3, 0, 4, Bishop );

#undef SETB
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

				((i + j + k) % 2 == 0 ? whiteSquare : blackSquare).Draw( XMMatrixTranslation( k * 3.0f, i * 6.0f, j * 3.0f ) );

				if ( pieces[i][j][k] )
					pieces[i][j][k]->Draw( k * 3.0f, i * 6.0f, j * 3.0f );

			}
		}
	}

	Window::Get().GetGraphics().SetBlendEnabled( true );
	Window::Get().GetGraphics().SetDepthEnabled( false );
	
	if ( selectedPos ) {
		PieceInfo info = PieceAt( *selectedPos ).GetInfo();
		highlightBox.Draw( XMMatrixScaling( info.diameter, info.height, info.diameter ) * XMMatrixTranslation( selectedPos->r * 3.0f, selectedPos->l * 6.0f, selectedPos->f * 3.0f ) );
	}
		
	Window::Get().GetGraphics().SetBlendEnabled( false );
	Window::Get().GetGraphics().SetDepthEnabled( true );

}

void Chess::MovePiece( PositionLFR from, PositionLFR to ) {
	CellAt( to ) = std::move( CellAt( from ) );
}

Piece& Chess::PieceAt( PositionLFR pos ) {
	return *CellAt( pos );

}

std::shared_ptr<Piece>& Chess::CellAt( PositionLFR pos ) {
	return pieces[pos.l][pos.f][pos.r];
}
