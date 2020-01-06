#pragma once

class Piece;

#include "Model.h"
#include "Player.h"
#include "Lighting.h"
#include "Client.h"
#include "Util.h"

#include <vector>
#include <array>
#include <memory>

/* 
An instance of Chess represents a current chess game.
It owns a Player object which is bound as the camera on construction
*/
class Chess {

public:
	Chess( const std::string& cmdLine );
	
	Chess( const Chess& ) = delete;
	Chess& operator=( const Chess& ) = delete;

	// call Update on the player and process messages from the server
	void Update( float dt );
	// render the board, pieces and highlighted boxes
	void Draw();
	// render the HUD
	void DrawHUD();
	// moves the piece at 'from' to 'to'
	void MovePiece( const PositionLFR& from, const PositionLFR& to );

private:
	// retrieve a reference to the shared_ptr that holds the piece at the specified position
	std::shared_ptr<Piece>& CellAt( PositionLFR p );
	std::shared_ptr<Piece>& CellAt( int l, int f, int r );

	// trace a ray and determine with piece was hit first by it
	std::optional<PositionLFR> PieceHit( const Ray& r );
	// trace a ray and determine which highlighted field was hit first by it
	std::optional<PositionLFR> HighlightHit( const Ray& r );

	// calculate a box with an appropriate size and positioning for the specified cell
	Box BoxAt( PositionLFR p );
	Box BoxAt( int l, int f, int r );

	/*
	nx5x5 array of shared pointers to pieces. The first index represents its level, second its file and third its rank.
	This means that in the first index will not be x, as that is its level and should be displayed on the y-axis.
	The outermost dimension is a vector so it is all dynamically allocated.
	sizeof( std::shared_ptr ) is 16 and 16 * 5 * 5 * 5 = 2000, too much for the stack.
	*/
	std::vector<std::array<std::array<std::shared_ptr<Piece>, 5>, 5>> pieces;

	Model whiteSquare, blackSquare;

	Light light; 
	ConstantBuffer<Light, PS, 1u> lightBuffer;

	std::unique_ptr<PositionLFR> selectedPos;
	std::vector<PositionLFR> highlights;
	
	std::vector<std::string> moveHistory;

	Player player;

	Client client;

	Side mySide;
	bool myTurn;
};
