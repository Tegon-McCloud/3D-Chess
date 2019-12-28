#pragma once

#include "Model.h"

#include <unordered_map>

enum Side {
	WHITE, BLACK
};

struct PieceInfo {
	char symbol;
	float diameter, height;
};

class Piece {

public:
	Piece( const std::string& piece, Side s );

	void Draw( float x, float y, float z );

	const PieceInfo& GetInfo();

private:
	std::shared_ptr<Model> pModel;
	PieceInfo info;
	Side side;

	static std::unordered_map< std::string, std::shared_ptr<Model> > models; // improve performance by only holding each model only once.
};