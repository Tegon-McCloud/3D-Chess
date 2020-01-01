#include "Player.h"
#include <algorithm>
#include <cmath>

Player::Player( const Box& movementBounds ) : Camera( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f ),
	bounds( movementBounds ) {}

void Player::Update( float dt ) {

	float sinYaw = sin( yaw );
	float cosYaw = cos( yaw );

	if ( Window::Get().GetInput().IsKeyDown( 'W' ) ) {
		x += 6.0f * dt * sinYaw;
		z += 6.0f * dt * cosYaw;
	}

	if ( Window::Get().GetInput().IsKeyDown( 'A' ) ) {
		x += 6.0f * dt * cosYaw;
		z += 6.0f * dt * -sinYaw;
	}

	if ( Window::Get().GetInput().IsKeyDown( 'S' ) ) {
		x += 6.0f * dt * -sinYaw;
		z += 6.0f * dt * -cosYaw;
	}

	if ( Window::Get().GetInput().IsKeyDown( 'D' ) ) {
		x += 6.0f * dt * -cosYaw;
		z += 6.0f * dt * sinYaw;
	}

	if ( Window::Get().GetInput().IsKeyDown( ' ' ) ) {
		y += 6.0f * dt;
	}
	
	if ( Window::Get().GetInput().IsKeyDown( VK_SHIFT ) ) {
		y -= 6.0f * dt;
	}
	
	x = std::max( x, bounds.min.x );
	y = std::max( y, bounds.min.y );
	z = std::max( z, bounds.min.z );
	x = std::min( x, bounds.max.x );
	y = std::min( y, bounds.max.y );
	z = std::min( z, bounds.max.z );

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
