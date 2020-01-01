#include "Chess.h"
#include "Piece.h"
#include "Util.h"

#include <algorithm>
#include <limits>
#include <iostream>

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

constexpr const Material mtlMove = {
	{					// color
		0.1f,				// r
		0.1f,				// g
		0.5f				// b
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

constexpr const Material mtlCapture = {
	{					// color
		0.5f,				// r
		0.1f,				// g
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
Chess::Chess( const std::string& cmdLine ) : 
	pieces(5, std::array<std::array<std::shared_ptr<Piece>, 5>, 5>()), 
	whiteSquare( "Square", mtlWhiteSquare ), 
	blackSquare( "Square", mtlBlackSquare ),
	client( cmdLine ),
	mySide( WHITE ),
	myTurn( false ),
	player( Box( -20.0f, -20.0f, -20.0f, 35.0f, 50.0f, 35.0f ) ) {

	player.Update( 0.0f );
	player.Bind();

	Window::Get().GetInput().RegisterClickListener( [ this ]( int x, int y ) -> void {

		using namespace DirectX;
		
		if ( !myTurn ) return;

		if ( selectedPos ) {
			
			std::optional<PositionLFR> hitpos = HighlightHit( player.LookRay() );

			if ( hitpos ) {
				client.SendMSG( std::string( "m:" ) +
								Position( *selectedPos ).ToAlg() +
								Position( hitpos.value() ).ToAlg()
				);
			} else {
				selectedPos.reset();
			}

		} else {
			std::optional<PositionLFR> hitpos = PieceHit( player.LookRay() );
			
			if ( hitpos ) {

				selectedPos.reset( new PositionLFR( hitpos.value() ) );
				client.SendMSG( std::string( "p:" ) 
								+ Position( *selectedPos ).ToAlg()
				);
			}
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
	SETB( 3, 1, 4, Bishop );
	SETB( 3, 2, 4, Queen );
	SETB( 3, 3, 4, Unicorn );
	SETB( 3, 4, 4, Bishop );

#undef SETB
}

void Chess::Update( float dt ) {
	player.Update( dt );

	std::string msg;

	while ( client.GetMSG( msg ) ) {
		printf( "processing: %s\n", msg.c_str() );

		switch ( msg[0] ) {
		case 'p':
			highlights.clear();
			msg.erase( 0, 2 );

			while ( msg.length() != 0 ) {
				highlights.push_back( Position( msg ).lfr );
				msg.erase( 0, 4 );
			}
			break;

		case 'm': 
		{ // new scope to avoid errors with declaring 'from' and 'to'
			highlights.clear();
			selectedPos.reset();

			msg.erase( 0, 2 );
			Position from( msg );
			msg.erase( 0, 3 );
			Position to( msg );

			MovePiece( from.lfr, to.lfr );
			break;
		}
		case 't':
			myTurn = (msg[2] == 'b') ^ (mySide == WHITE);
			break;

		case 's':
			mySide = msg[2] == 'w' ? WHITE : BLACK;
			break;

#ifdef _DEBUG
		default:
			std::cout << "Unknown command received from server:\n" << msg << "\n";
#endif // _DEBUG
		}

	}

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
		
		BoxAt( *selectedPos ).Draw( mtlSelected );

		for ( auto it = highlights.cbegin(); it != highlights.cend(); it++ ) {
			BoxAt( *it ).Draw( CellAt( *it ) ? mtlCapture : mtlMove );
		}

	}
		
	Window::Get().GetGraphics().SetBlendEnabled( false );
	Window::Get().GetGraphics().SetDepthEnabled( true );

}

void Chess::MovePiece( const PositionLFR& from, const PositionLFR& to ) {
	CellAt( to ) = std::move( CellAt( from ) );
}

std::shared_ptr<Piece>& Chess::CellAt( PositionLFR pos ) {
	return pieces[pos.l][pos.f][pos.r];
}

std::shared_ptr<Piece>& Chess::CellAt( int l, int f, int r ) {
	return pieces[l][f][r];
}

std::optional<PositionLFR> Chess::PieceHit( const Ray& r ) {

	PositionLFR hitpos( -1, -1, -1 );
	float dist = std::numeric_limits<float>::infinity();
	
	for ( int i = 0; i < 5; i++ ) {
		for ( int j = 0; j < 5; j++ ) {
			for ( int k = 0; k < 5; k++ ) {
				if ( CellAt( i, j, k ) ) {

					float t = intersection( r, BoxAt( i, j, k ) );
					if ( t < dist ) {
						dist = t;
						hitpos = PositionLFR( i, j, k );
					}

				}
			}
		}
	}

	if ( hitpos.l != -1 ) {
		return hitpos;
	} else {
		return std::optional<PositionLFR>();
	}
}

std::optional<PositionLFR> Chess::HighlightHit( const Ray& r ) {

	if ( !selectedPos || !CellAt( *selectedPos ) || highlights.empty() ) return std::optional<PositionLFR>();
	
	PositionLFR hitpos( -1, -1, -1 );
	float dist = std::numeric_limits<float>::infinity();

	for ( auto it = highlights.cbegin(); it != highlights.cend(); it++ ) {
		
		float t = intersection( r, BoxAt( *it ) );

		if ( t < dist ) {
			dist = t;
			hitpos = *it;
		}
	}

	if ( hitpos.l != -1 ) {
		return hitpos;
	} else {
		return std::optional<PositionLFR>();
	}
}

Box Chess::BoxAt( PositionLFR p ) {
	
	PieceInfo info;
	std::shared_ptr<Piece> cell = CellAt( p );

	if( cell ) {
		info = cell->GetInfo();
	} else if ( selectedPos && (cell = CellAt( *selectedPos )) != nullptr ) {
		info = cell->GetInfo();
	} else {
		info.diameter = 1.0f;
		info.height = 1.0f;
		info.symbol = '?';
	}
	
	Box b;

	b.min.x = p.r * 3.0f - 0.5f * info.diameter;
	b.min.y = p.l * 6.0f - 0.0f * info.height;
	b.min.z = p.f * 3.0f - 0.5f * info.diameter;

	b.max.x = p.r * 3.0f + 0.5f * info.diameter;
	b.max.y = p.l * 6.0f + 1.0f * info.height;
	b.max.z = p.f * 3.0f + 0.5f * info.diameter;

	return b;
}

Box Chess::BoxAt( int l, int f, int r ) {
	return BoxAt( PositionLFR( l, f, r ) );
}
