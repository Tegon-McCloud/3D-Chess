#pragma once

#include "Pieces.h"

#include <array>
#include <memory>
#include "Player.h"

constexpr const Material mtlWhite = {
	{					// ambient:
		0.2f				// intensity
	},
	{					// diffuse:
		1.0f,				// r
		1.0f,				// g
		1.0f				// b
	},
	{					// specular:
		0.1,				// intensity
		24.0f				// shininess
	}
};

constexpr const Material mtlBlack = {
	{					// ambient:
		0.2f				// intensity
	},
	{					// diffuse:
		0.1f,				// r
		0.1f,				// g
		0.1f				// b
	},
	{					// specular:
		0.1,				// intensity
		24.0f				// shininess
	}
};

class Chess {

public:
	Chess();

	void Update( float dt );
	void Draw();

private:
	std::array< std::array< std::array< std::shared_ptr< Piece >, 5 >, 5 >, 5 > pieces;
	std::array< std::array< std::array< std::shared_ptr< Model >, 5 >, 5 >, 5 > board;
	//ConstantBuffer< Light,  >

	Player player;
};
