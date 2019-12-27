#pragma once

#include "Pieces.h"
#include "Player.h"
#include "Lighting.h"
#include "Util.h"

#include <array>
#include <memory>

/* 
An instance of Chess represents a current chess game.
It owns a Player object which is bound as the camera on construction
*/
class Chess {

public:
	Chess();
	
	Chess( const Chess& ) = delete;
	Chess& operator=( const Chess& ) = delete;

	void Update( float dt );
	void Draw();
	void MovePiece( PositionLFR from, PositionLFR to );

	Piece& PieceAt( PositionLFR p );

private:

	std::shared_ptr<Piece>& CellAt( PositionLFR p );

	/*
	nx5x5 array of shared pointers to pieces. The first index will be its level, second its file and third its rank.
	This means that in the first index will not be x, as that is its level and should naturally be displayed on the y-axis.
	The outermost dimension is a vector so it is all allocated on heap.
	sizeof( std::shared_ptr ) is 16 and 16 * 5 * 5 * 5 = 2000, too much for the stack.
	*/
	std::vector<std::array<std::array<std::shared_ptr<Piece>, 5>, 5>> pieces;

	// The models of a black and white square.
	Model whiteSquare, blackSquare;
	// model of a 1x1x1 box, used for highlighting various positions.
	Model highlightBox;

	// a pointer to a Position that is currently selected by the player
	std::unique_ptr<PositionLFR> selectedPos;


	Light light; 
	ConstantBuffer<Light, PS, 1u> lightBuffer;

	Player player;
};
