#pragma once

#include "Pieces.h"
#include "Player.h"
#include "Lighting.h"
#include "Util.h"

#include <array>
#include <memory>

/* An instance of Chess represents a current chess game. 
 */
class Chess {

public:
	Chess();

	void Update( float dt );
	void Draw();
	void MovePiece( PositionLFR from, PositionLFR to );

	Piece& PieceAt( PositionLFR p );
	
private:

	std::shared_ptr<Piece>& CellAt( PositionLFR p );

	/* The board is a 5x5x5 array of pieces. The first index will be its level, second its file and third its rank.
	 * This means that in the first index will not be x, as that is its level and should naturally be displayed on the y-axis.
	 */
	std::array< std::array< std::array< std::shared_ptr< Piece >, 5 >, 5 >, 5 > pieces;
	std::array< std::array< std::array< std::shared_ptr< Model >, 5 >, 5 >, 5 > board;
	std::shared_ptr<Model> highlightBox;
	std::unique_ptr<PositionLFR> selectedPos;

	Light light;
	ConstantBuffer < Light, PS, 1u > lightBuffer;

	Player player;

	
};
