#include "MoveLog.h"
#include "Chess.h"
#include "Window.h"
#include "Piece.h"

#include <cstdlib>

MoveLog::MoveLog() {

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

constexpr int lineHeight = 18;

void MoveLog::Draw() const {

	D2D1_SIZE_F targetSize = Window::GFX().GetTargetDipSize();

	float bottom = 264.0f;

	D2D1_RECT_F whiteRect = D2D1::RectF(
		targetSize.width - 176.0f,
		8.0f,
		targetSize.width - 96.0f,
		bottom
	);

	D2D1_RECT_F blackRect = D2D1::RectF(
		targetSize.width - 88.0f,
		8.0f,
		targetSize.width - 8.0f,
		bottom
	);

	Window::GFX().GetContext2D()->FillRectangle( whiteRect, pWBackgroundBrush.Get() );
	Window::GFX().GetContext2D()->FillRectangle( blackRect, pBBackgroundBrush.Get() );
	
	whiteRect = D2D1::RectF(
		whiteRect.left + 5,
		whiteRect.top + 2,
		whiteRect.right - 5,
		whiteRect.top + 2 + lineHeight
	);

	blackRect = D2D1::RectF(
		blackRect.left + 5,
		blackRect.top + 2,
		blackRect.right - 5,
		blackRect.top + 2 + lineHeight
	);

	Window::GFX().GetContext2D()->DrawTextW( L"White", 5, pTextFormat.Get(), whiteRect, pBTextBrush.Get() );
	Window::GFX().GetContext2D()->DrawTextW( L"Black", 5, pTextFormat.Get(), blackRect, pWTextBrush.Get() );

	for ( size_t i = 0; i + scroll * 2 < moves.size(); i++ ) {
		const D2D1_RECT_F& rect = whiteRect;
		const std::wstring& str = moves[i + scroll * 2];

		if ( i % 2 == 0 ) {
			whiteRect.top += lineHeight;
			whiteRect.bottom += lineHeight;
			if ( whiteRect.bottom > bottom ) break;

			Window::GFX().GetContext2D()->DrawTextW( str.c_str(), str.size(), pTextFormat.Get(), whiteRect, pBTextBrush.Get() );

		} else {
			blackRect.top += lineHeight;
			blackRect.bottom += lineHeight;

			Window::GFX().GetContext2D()->DrawTextW( str.c_str(), str.size(), pTextFormat.Get(), blackRect, pWTextBrush.Get() );
		}
	}

}

void MoveLog::AddMove( const Chess& game, const PositionLFR& p1, const PositionLFR& p2 ) {
	
	std::wstring move;

	move.push_back( game.PieceAt( p1 ).GetInfo().symbol );
	move.push_back( ' ' );

	move += std::wstring(  );

	moves.push_back( move );
}
