#include "Player.h"

#include "Util.h"
#include "d2d1effects_2.h"
#include <algorithm>
#include <cmath>

Player::Player( const Box& movementBounds ) : Camera( 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f ),
	bounds( movementBounds ) {

	D2D1_BITMAP_PROPERTIES1 bmp;
	bmp.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
	bmp.pixelFormat.alphaMode = D2D1_ALPHA_MODE_IGNORE;
	bmp.bitmapOptions = D2D1_BITMAP_OPTIONS_NONE;
	bmp.colorContext = NULL;
	bmp.dpiX = Window::GFX().GetDpiXScale() * 96.0f;
	bmp.dpiY = Window::GFX().GetDpiYScale() * 96.0f;

	ThrowIfFailed( Window::GFX().GetContext2D()->CreateBitmap( D2D1::SizeU( 24, 2 ), NULL, 0, &bmp, &pHorzBar ) );
	ThrowIfFailed( Window::GFX().GetContext2D()->CreateBitmap( D2D1::SizeU( 2, 24 ), NULL, 0, &bmp, &pVertBar ) );

	ThrowIfFailed( Window::GFX().GetContext2D()->CreateEffect( CLSID_D2D1Invert, &pInvert ) );
}

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

void Player::DrawHUD() const {

	D2D1_POINT_2U targetCenter = *reinterpret_cast<D2D1_POINT_2U*>(&Window::GFX().GetTargetSize());
	targetCenter.x /= 2;
	targetCenter.y /= 2;

	D2D1_RECT_U r;

	r = D2D1::RectU( targetCenter.x - 12, targetCenter.y - 1, targetCenter.x + 12, targetCenter.y + 1 );
	ThrowIfFailed( pHorzBar->CopyFromBitmap( NULL, Window::GFX().GetTarget2D(), &r ) );
	pInvert->SetInput( 0, pHorzBar.Get() );
	Window::GFX().GetContext2D()->DrawImage( pInvert.Get(), D2D1::Point2F( r.left * Window::GFX().GetDpiXScale(), r.top * Window::GFX().GetDpiYScale() ) );
	
	r = D2D1::RectU( targetCenter.x - 1, targetCenter.y - 12, targetCenter.x + 1, targetCenter.y + 12 );
	ThrowIfFailed( pVertBar->CopyFromBitmap( NULL, Window::GFX().GetTarget2D(), &r ) );
	pInvert->SetInput( 0, pVertBar.Get() );
	Window::GFX().GetContext2D()->DrawImage( pInvert.Get(), D2D1::Point2F( r.left * Window::GFX().GetDpiXScale(), r.top * Window::GFX().GetDpiYScale() ) );
}
