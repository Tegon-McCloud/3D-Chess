#include "HUD.h"
#include "Window.h"

HUD::HUD() {

	Window::GFX().GetContext2D()->CreateSolidColorBrush( D2D1::ColorF( 1.0f, 1.0f, 1.0f, 1.0f ), &pWTextBrush );
	Window::GFX().GetContext2D()->CreateSolidColorBrush( D2D1::ColorF( 0.0f, 0.0f, 0.0f, 1.0f ), &pBTextBrush );
	Window::GFX().GetContext2D()->CreateSolidColorBrush( D2D1::ColorF( 1.0f, 1.0f, 1.0f, 0.5f ), &pWBackgroundBrush );
	Window::GFX().GetContext2D()->CreateSolidColorBrush( D2D1::ColorF( 0.0f, 0.0f, 0.0f, 0.5f ), &pBBackgroundBrush );
	
	Window::GFX().GetWriteFactory()->CreateTextFormat(
		L"Courier New",
		NULL,
		DWRITE_FONT_WEIGHT_MEDIUM,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		12.0f,
		L"en-us",
		&pTextFormat
	);

}

void HUD::DrawMoveLog( const std::vector<std::wstring>& moves ) const {

	D2D1_SIZE_F targetSize = Window::GFX().GetTargetDipSize();

	D2D1_RECT_F MoveLogWhite = D2D1::RectF( targetSize.width - 110, 10, targetSize.width - 60, targetSize.height - 10 );
	D2D1_RECT_F MoveLogBlack = D2D1::RectF( targetSize.width - 55, 10, targetSize.width - 5, targetSize.height - 10 );

	Window::GFX().GetContext2D()->FillRectangle( MoveLogWhite, pWBackgroundBrush.Get() );
	Window::GFX().GetContext2D()->FillRectangle( MoveLogBlack, pBBackgroundBrush.Get() );

	MoveLogWhite.left += 5;
	MoveLogBlack.left += 5;

	Window::GFX().GetContext2D()->DrawTextW( L"White", 5, pTextFormat.Get(), MoveLogWhite, pBTextBrush.Get() );
	Window::GFX().GetContext2D()->DrawTextW( L"Black", 5, pTextFormat.Get(), MoveLogBlack, pWTextBrush.Get() );



}
