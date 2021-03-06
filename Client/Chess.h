 #pragma once

#include "Piece.h"
#include "Model.h"
#include "Player.h"
#include "Lighting.h"
#include "Client.h"
#include "Util.h"
#include "MoveLog.h"

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
	void Draw() const;
	// render the HUD
	void DrawHUD() const;
	// moves the piece at 'from' to 'to'
	void MovePiece( const PositionLFR& from, const PositionLFR& to );
	
	const Piece& PieceAt( const PositionLFR& p ) const;

private:
	// retrieve a reference to the shared_ptr that holds the piece at the specified position
	std::shared_ptr<Piece>& CellAt( const PositionLFR& pos );
	std::shared_ptr<Piece>& CellAt( int l, int f, int r );
	const std::shared_ptr<Piece>& CellAt( const PositionLFR& pos ) const;
	const std::shared_ptr<Piece>& CellAt( int l, int f, int r ) const;

	// cast a ray and determine with piece was hit first by it
	std::optional<PositionLFR> PieceHit( const Ray& r ) const;
	// cast a ray and determine which highlighted field was hit first by it
	std::optional<PositionLFR> HighlightHit( const Ray& r ) const;
	// cast a ray and determine which promotion piecemodel was hit by it
	char PromotionHit( const Ray& r ) const;

	// calculate a box with an appropriate size and positioning for the specified cell
	Box BoxAt( PositionLFR p ) const;
	Box BoxAt( int l, int f, int r ) const;

	/*
	nx5x5 array of shared pointers to pieces. The first index represents its level, second its file and third its rank.
	This means that in the first index will not be x, as that is its level and should be displayed on the y-axis.
	The outermost dimension is a vector so it is all dynamically allocated.
	*/
	std::vector<std::array<std::array<std::shared_ptr<Piece>, 5>, 5>> pieces;

	Model whiteSquare, blackSquare;

	Light light; 
	ConstantBuffer<Light, PS, 1u> lightBuffer;

	std::unique_ptr<PositionLFR> selectedPos;
	std::vector<PositionLFR> highlights;

	std::vector<Piece> promotionPieces;
	std::optional<PositionLFR> promotionPos;

	Player player;
	MoveLog moveLog;

	Client client;

	Side mySide;
	char winner;
	bool myTurn;
};
