#pragma once

#include "Camera.h"
#include "Util.h"

#include "d2d1_1.h"
#include <memory>

/*
Player is a specialized Camera, that moves when pressing WASD and rotates when mouse is moved.
Every frame the Update() method must be called with how much time has passed as an argument, in order to
move the camera the correct distant and update the cameras buffers.
*/
class Player : public Camera {

public:
	Player( const Box& movementBounds = Box(
		-std::numeric_limits<float>::infinity(),
		-std::numeric_limits<float>::infinity(),
		-std::numeric_limits<float>::infinity(),
		std::numeric_limits<float>::infinity(),
		std::numeric_limits<float>::infinity(),
		std::numeric_limits<float>::infinity()
	));

	void Update( float dt );
	void DrawHUD();

private:

	Box bounds;

	Microsoft::WRL::ComPtr<ID2D1Bitmap1> pHorzBar;
	Microsoft::WRL::ComPtr<ID2D1Bitmap1> pVertBar;
	Microsoft::WRL::ComPtr<ID2D1Effect> pInvert;

};

