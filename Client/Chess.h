#pragma once

#include "Pieces.h"

#include <array>
#include <memory>
#include "Player.h"

class Chess {

public:
	Chess();

	void Update( float dt );
	void Draw();

private:
	std::array< std::array< std::array< std::shared_ptr< Piece >, 5 >, 5 >, 5 > board;



	Player player;
};

