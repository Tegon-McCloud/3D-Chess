#pragma once
#include "Model.h"
#include "Pieces.h"
#include <array>
#include <memory>

class Chess {

public:
	Chess();

	void Draw();

private:
	std::array< std::array< std::array< std::unique_ptr< Piece >, 5 >, 5 >, 5 > board;

};

