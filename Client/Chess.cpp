#include "Chess.h"
#include "Piece.h"
#include "Util.h"

#include "d2d1_1.h"
#include "d2d1effects_2.h"
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
	pieces( 5, std::array<std::array<std::shared_ptr<Piece>, 5>, 5>() ),
	whiteSquare( "Square", mtlWhiteSquare ),
	blackSquare( "Square", mtlBlackSquare ),
	client( cmdLine ),
	mySide( Side::WHITE ),
	winner( 'n' ), // n for none
	myTurn( false ),
	player( Box( -20.0f, -20.0f, -20.0f, 32.0f, 50.0f, 32.0f ) )
	{

	player.Update( 0.0f ); // update player with delta time = 0 to ensure it is fully initialized
	player.Bind(); // bind player as the camera

	Window::Get().GetInput().RegisterClickListener( [ this ]( int x, int y ) -> void { // register a listener for when the player clicks

		using namespace DirectX;
		
		if ( !myTurn ) return;

		if ( promotionPos ) {
			
			char c = PromotionHit( player.LookRay() );
			client.SendMSG( std::string( "p:" ) + c + Position( promotionPos.value() ).ToAlg() );
			return;
		}


		if ( selectedPos ) { // if the player has currently selected a position
			
			std::optional<PositionLFR> hitpos = HighlightHit( player.LookRay() ); // find which highlight box the player clicked (or none)

			if ( hitpos ) { // if the player clicked a box
				client.SendMSG( std::string( "m:" ) +	// tell the server to move the selected piece to the clicked position
								Position( *selectedPos ).ToAlg() +	
								Position( hitpos.value() ).ToAlg()
				);
			} else {
				selectedPos.reset();
			}

		} else { // if no position is selected
			std::optional<PositionLFR> hitpos = PieceHit( player.LookRay() ); // find out what piece the player clicked (if any) 
			
			if ( hitpos ) {
				selectedPos.reset( new PositionLFR( hitpos.value() ) ); // select that piece
				highlights.clear();
				
				client.SendMSG( std::string( "l:" ) + Position( *selectedPos ).ToAlg() ); // request list of moves from selected position 
			}
		}



	} );

	// setup scene lighting
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
					pieces[i][j][k].reset(new Piece( "Pawn", Side::WHITE ));
				}

				if ( k == 3 && i > 2 ) {
					pieces[i][j][k].reset(new Piece( "Pawn", Side::BLACK ));
				}
				
			}
		}
	}

#define SETW(l, f, r, piece) pieces[l][f][r].reset( new Piece( #piece, Side::WHITE ) )
	
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
#define SETB(l, f, r, piece) pieces[l][f][r].reset( new Piece( #piece, Side::BLACK ) );
	
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
	using namespace DirectX;

	// player
	player.Update( dt );

	// lighting
	const XMVECTOR lightDirWorld = XMVector3Normalize( { 1.0f, -1.0f, 1.0f, 0.0f } );
	XMVECTOR lightDirView = player.ToViewSpace4( lightDirWorld );

	XMStoreFloat3( &light.dir, lightDirView );

	lightBuffer.Set( &light );

	// message handling
	std::string msg;

	while ( client.GetMSG( msg ) ) {

#ifdef _DEBUG
		printf( "processing: %s\n", msg.c_str() );
#endif // _DEBUG

		switch ( msg[0] ) {
		case 'l': // the server has provided a list of moves
			highlights.clear();
			msg.erase( 0, 2 );

			while ( msg.length() != 0 ) {
				highlights.push_back( Position( msg ).lfr );
				msg.erase( 0, 4 );
			}
			break;

		case 'm': // the server has made a move and asks this client to mirror it
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
		case 't': // it is the specified clients turn
			myTurn = (msg[2] == 'b') ^ (mySide == Side::WHITE);
			break;

		case 's': // the server has given this client a color
			mySide = msg[2] == 'w' ? Side::WHITE : Side::BLACK;
			
			if ( mySide == Side::WHITE ) {
				// set position and direction for white side
				player.SetPosition( -12.0f, 6.0f, 6.0f );
				player.SetDirection( pi/2.0f, 0.0f, 0.0f );
			} else {
				// set position and direction for black side
				player.SetPosition( 12.0f + 12.0f, 24.0f - 6.0f, 12.0f - 6.0f );
				player.SetDirection( -pi / 2.0f, 0.0f, 0.0f );
			}

			promotionPieces.clear();
			promotionPieces.push_back( Piece( "Queen", mySide ) );
			promotionPieces.push_back( Piece( "Knight", mySide ) );
			promotionPieces.push_back( Piece( "Unicorn", mySide ) );
			promotionPieces.push_back( Piece( "Bishop", mySide ) );
			promotionPieces.push_back( Piece( "Rook", mySide ) );

			break;
		
		case 'd': // the game has ended, either because the server was shutdown or the other client disconnected
			client.Disconnect();
			break;

		case 'v':
			winner = msg[2];
			break;
		case 'p':
			msg.erase( 0, 2 );
			if ( msg.length() == 3 ) {
				promotionPos = Position( msg ).lfr;
			} else {
				Piece* piece = nullptr;

				switch ( msg[0] ) {
				case 'Q':
					piece = new Piece( "Queen", mySide );
					break;
				case 'N':
					piece = new Piece( "Knight", mySide );
					break;
				case 'U':
					piece = new Piece( "Unicorn", mySide );
					break;
				case 'B':
					piece = new Piece( "Bishop", mySide );
					break;
				case 'R':
					piece = new Piece( "Rook", mySide );
					break;
				}


				CellAt( promotionPos.value() ).reset( piece ) ;
				promotionPos.reset();
			}

			break;
#ifdef _DEBUG
		default:
			std::cout << "Unknown command received from server:\n" << msg << "\n";
#endif // _DEBUG
		}

	}
}

void Chess::Draw() const {
	using namespace DirectX;

	for ( int i = 0; i < 5; i++ ) {
		for ( int j = 0; j < 5; j++ ) {
			for ( int k = 0; k < 5; k++ ) {

				((i + j + k) % 2 == 0 ? whiteSquare : blackSquare).Draw( XMMatrixTranslation( k * 3.0f, i * 6.0f, j * 3.0f ) );

				if ( pieces[i][j][k] ) // if square has a piece
					pieces[i][j][k]->Draw( k * 3.0f, i * 6.0f, j * 3.0f );

			}
		}
	}

	Window::Get().GetGraphics().SetDepthEnabled( false );
	
	if ( selectedPos ) {
		
		BoxAt( *selectedPos ).Draw( mtlSelected );

		for ( auto it = highlights.cbegin(); it != highlights.cend(); it++ ) {
			BoxAt( *it ).Draw( CellAt( *it ) ? mtlCapture : mtlMove );
		}
	}

	Window::Get().GetGraphics().SetDepthEnabled( true );

	if ( promotionPos.has_value() ) {
		const Model& square = (promotionPos->l + promotionPos->f + promotionPos->r) % 2 == 0 ? whiteSquare : blackSquare;
		
 		for ( int i = 0; i < promotionPieces.size(); i++ ) {
			int r = mySide == Side::WHITE ? (promotionPos->r + i + 1) : (promotionPos->r - i - 1);
			int l = promotionPos->l;
			int f = promotionPos->f;
			square.Draw( XMMatrixTranslation( r * 3.0f, l * 6.0f, f * 3.0f ) );
			promotionPieces[i].Draw( r * 3.0f, l * 6.0f, f * 3.0f );
		}
	}

}

void Chess::DrawHUD() const {
	moveLog.Draw();
	player.DrawHUD();
	
	switch ( winner ) {
	case 'w':
	case 'b':
		mySide == (winner == 'w' ? Side::WHITE : Side::BLACK) ? moveLog.DrawVictory() : moveLog.DrawDefeat();
		break;
	case 'd':
		moveLog.DrawDraw();
		break;
	}
}

void Chess::MovePiece( const PositionLFR& from, const PositionLFR& to ) {
	moveLog.AddMove( *this, from, to );
	CellAt( to ) = std::move( CellAt( from ) );
}

const Piece& Chess::PieceAt( const PositionLFR& p ) const {
	return *CellAt( p );
}

std::shared_ptr<Piece>& Chess::CellAt( const PositionLFR& pos ) {
	return pieces[pos.l][pos.f][pos.r];
}

std::shared_ptr<Piece>& Chess::CellAt( int l, int f, int r ) {
	return pieces[l][f][r];
}

const std::shared_ptr<Piece>& Chess::CellAt( const PositionLFR& pos ) const {
	return pieces[pos.l][pos.f][pos.r];
}

const std::shared_ptr<Piece>& Chess::CellAt( int l, int f, int r ) const {
	return pieces[l][f][r];
}

std::optional<PositionLFR> Chess::PieceHit( const Ray& r ) const {

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

std::optional<PositionLFR> Chess::HighlightHit( const Ray& r ) const {

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

char Chess::PromotionHit( const Ray& ray ) const {
	
	if ( !promotionPos ) return '0';

	char c = '0';
	float dist = std::numeric_limits<float>::infinity();

	Box b;

	for ( int i = 0; i < promotionPieces.size(); i++ ) {
		int r = mySide == Side::WHITE ? (promotionPos->r + i + 1) : (promotionPos->r - i - 1);
		int l = promotionPos->l;
		int f = promotionPos->f;

		const PieceInfo& info = promotionPieces[i].GetInfo();
		
		b.min.x = r * 3.0f - 0.5f * info.diameter;
		b.min.y = l * 6.0f - 0.0f * info.height;
		b.min.z = f * 3.0f - 0.5f * info.diameter;

		b.max.x = r * 3.0f + 0.5f * info.diameter;
		b.max.y = l * 6.0f + 1.0f * info.height;
		b.max.z = f * 3.0f + 0.5f * info.diameter;
		
		float t = intersection( ray, b );
		if ( t < dist ) {
			c = info.symbol;
			dist = t;
		}

	}

	return c;
}

Box Chess::BoxAt( PositionLFR p ) const {
	
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

Box Chess::BoxAt( int l, int f, int r ) const {
	return BoxAt( PositionLFR( l, f, r ) );
}
