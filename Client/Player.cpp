#include "Player.h"
#include <algorithm>
#include <cmath>

Player::Player() : Camera( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f ) {}

void Player::Update( float dt ) {

	float sinYaw = sin( yaw );
	float cosYaw = cos( yaw );

	if ( Window::Get().GetInput().IsKeyDown( 'W' ) ) {
		x += 4.0f * dt * sinYaw;
		z += 4.0f * dt * cosYaw;
	}

	if ( Window::Get().GetInput().IsKeyDown( 'A' ) ) {
		x += 4.0f * dt * cosYaw;
		z += 4.0f * dt * -sinYaw;
	}

	if ( Window::Get().GetInput().IsKeyDown( 'S' ) ) {
		x += 4.0f * dt * -sinYaw;
		z += 4.0f * dt * -cosYaw;
	}

	if ( Window::Get().GetInput().IsKeyDown( 'D' ) ) {
		x += 4.0f * dt * -cosYaw;
		z += 4.0f * dt * sinYaw;
	}

	if ( Window::Get().GetInput().IsKeyDown( ' ' ) ) {
		y += 4.0f * dt;
	}
	
	if ( Window::Get().GetInput().IsKeyDown( VK_SHIFT ) ) {
		y -= 4.0f * dt;
	}
	
	if ( Window::Get().IsInFocus() ) {
		POINT mp = Window::Get().GetInput().GetMousePos();
		mp.x -= Window::Get().GetWidth() / 2;
		mp.y -= Window::Get().GetHeight() / 2;

		yaw -= mp.x * 0.001f;
		pitch = std::clamp( pitch + mp.y * 0.001f, -1.57f, 1.57f );

		Window::Get().GetInput().CenterMouse();
	}

	UpdateBuffer();
}
