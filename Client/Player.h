#pragma once

#include "Camera.h"


/*
Player is a specialized Camera, that moves when pressing WASD and rotates when mouse is moved.
Every frame the Update() method must be called with how much time has passed as an argument, in order to
move the camera the correct distant and update the cameras buffers.
*/
class Player : public Camera {

public:

	Player();
	void Update( float dt );

};

