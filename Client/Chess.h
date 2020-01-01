#pragma once

class Piece;
struct PositionLFR;

#include "Model.h"
#include "Player.h"
#include "Lighting.h"
#include "Client.h"

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

	void Update( float dt );
	void Draw();
	void MovePiece( PositionLFR from, PositionLFR to );

	Piece& PieceAt( PositionLFR p );

private:

	void ForEachPos( std::function<void(int, int, int)> f );

	std::shared_ptr<Piece>& CellAt( PositionLFR p );
	std::shared_ptr<Piece>& CellAt( int l, int f, int r );

	std::optional<PositionLFR> PieceHit( const Ray& r );
	std::optional<PositionLFR> HighlightHit( const Ray& r );

	Box BoxAt( PositionLFR p );
	Box BoxAt( int l, int f, int r );

	/*
	nx5x5 array of shared pointers to pieces. The first index represents its level, second its file and third its rank.
	This means that in the first index will not be x, as that is its level and should be displayed on the y-axis.
	The outermost dimension is a vector so it is all dynamically allocated.
	sizeof( std::shared_ptr ) is 16 and 16 * 5 * 5 * 5 = 2000, too much for the stack.
	*/
	std::vector<std::array<std::array<std::shared_ptr<Piece>, 5>, 5>> pieces;

	// models of a black and white square.
	Model whiteSquare, blackSquare;

	// a pointer to a Position that is currently selected by the player
	std::unique_ptr<PositionLFR> selectedPos;
	// the positions that are currently highlighted
	std::vector<PositionLFR> highlights;
	
	Light light; 
	ConstantBuffer<Light, PS, 1u> lightBuffer;

	Player player;

	Client client;
};
