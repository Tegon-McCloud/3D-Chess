#include "MoveLog.h"
#include "Chess.h"
#include "Window.h"
#include "Piece.h"

#include <cstdlib>
#include <stdint.h>
#include <iostream>

MoveLog::MoveLog() :
	scroll( 0 ) {

	Window::Get().GetInput().RegisterMouseWheelListener(
		[this]( int delta ) -> void {
			if ( scroll >= delta && (scroll - delta) * 2 < moves.size() ) {
				scroll -= delta;
			}

			if ( (int64_t)scroll <= delta ) {
				scroll = 0;
			} else if ( (scroll - delta) * 2 >= moves.size() ) {
				scroll = (moves.size() + 1) / 2;
			} else {
				scroll -= delta;
			}
		}
	);
	ThrowIfFailed( Window::GFX().GetContext2D()->CreateSolidColorBrush( D2D1::ColorF( 1.0f, 1.0f, 1.0f, 1.0f ), &pBTextBrush ) );
	ThrowIfFailed( Window::GFX().GetContext2D()->CreateSolidColorBrush( D2D1::ColorF( 0.0f, 0.0f, 0.0f, 1.0f ), &pWTextBrush ) );
	ThrowIfFailed( Window::GFX().GetContext2D()->CreateSolidColorBrush( D2D1::ColorF( 1.0f, 1.0f, 1.0f, 0.2f ), &pBBackgroundBrush ) );
	ThrowIfFailed( Window::GFX().GetContext2D()->CreateSolidColorBrush( D2D1::ColorF( 0.0f, 0.0f, 0.0f, 0.2f ), &pWBackgroundBrush ) );
	
	ThrowIfFailed( Window::GFX().GetWriteFactory()->CreateTextFormat(
		L"Courier New",
		NULL,
		DWRITE_FONT_WEIGHT_MEDIUM,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		12.0f,
		L"en-us",
		&pTextFormat
	) );

	ThrowIfFailed( Window::GFX().GetWriteFactory()->CreateTextFormat(
		L"Courier New",
		NULL,
		DWRITE_FONT_WEIGHT_MEDIUM,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		96.0f,
		L"en-us",
		&pBigTextFormat
	) );

	ThrowIfFailed( pBigTextFormat->SetTextAlignment( DWRITE_TEXT_ALIGNMENT_CENTER ) );
	ThrowIfFailed( pBigTextFormat->SetParagraphAlignment( DWRITE_PARAGRAPH_ALIGNMENT_CENTER ) );
}

constexpr int lineHeight = 18;

void MoveLog::Draw() const {

	D2D1_SIZE_U targetSize = Window::GFX().GetTargetSize();

	float bottom = 264.0f;

	D2D1_RECT_F whiteRect = D2D1::RectF(
		targetSize.width - 220.0f,
		8.0f,
		targetSize.width - 120.0f,
		bottom
	);

	D2D1_RECT_F blackRect = D2D1::RectF(
		targetSize.width - 110.0f,
		8.0f,
		targetSize.width - 10.0f,
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

			Window::GFX().GetContext2D()->DrawTextW( str.c_str(), (UINT32)str.size(), pTextFormat.Get(), whiteRect, pBTextBrush.Get() );

		} else {
			blackRect.top += lineHeight;
			blackRect.bottom += lineHeight;

			Window::GFX().GetContext2D()->DrawTextW( str.c_str(), (UINT32)str.size(), pTextFormat.Get(), blackRect, pWTextBrush.Get() );
		}
	}

}

void MoveLog::AddMove( const Chess& game, const PositionLFR& p1, const PositionLFR& p2 ) {
	
	std::wstring move;
	
	move.push_back( game.PieceAt( p1 ).GetInfo().symbol );
	move.push_back( ' ' );

	std::string alg = Position( p1 ).ToAlg();
	move += std::wstring( alg.cbegin(), alg.cend() );
	move += L"\U00008594";
	alg = Position( p2 ).ToAlg();
	move += std::wstring( alg.cbegin(), alg.cend() );

	moves.push_back( move );
}

void MoveLog::DrawVictory() const {

	D2D1_SIZE_U targetSize = Window::GFX().GetTargetSize();
	
	const D2D1_RECT_F rect = D2D1::RectF( // the rect to draw in
		(float)targetSize.width / 2.0f - 600.0f,
		(float)targetSize.height / 2.0f - 300.0f,
		(float)targetSize.width / 2.0f + 600.0f,
		(float)targetSize.height / 2.0f + 000.0f
	);

	Window::GFX().GetContext2D()->FillRectangle( &rect, pWBackgroundBrush.Get() );
	Window::GFX().GetContext2D()->DrawTextW(
		L"Victory", 7ui32,
		pBigTextFormat.Get(),
		&rect, pBTextBrush.Get() );
}

void MoveLog::DrawDefeat() const {
	D2D1_SIZE_U targetSize = Window::GFX().GetTargetSize();

	const D2D1_RECT_F rect = D2D1::RectF( // the rect to draw in
		(float)targetSize.width / 2.0f - 600.0f,
										  (float)targetSize.height / 2.0f - 300.0f,
										  (float)targetSize.width / 2.0f + 600.0f,
										  (float)targetSize.height / 2.0f + 000.0f
	);

	Window::GFX().GetContext2D()->FillRectangle( &rect, pBBackgroundBrush.Get() );
	Window::GFX().GetContext2D()->DrawTextW(
		L"Defeat", 6ui32,
		pBigTextFormat.Get(),
		&rect, pWTextBrush.Get() );
}

void MoveLog::DrawDraw() const {

	D2D1_SIZE_U targetSize = Window::GFX().GetTargetSize();

	const D2D1_RECT_F rect = D2D1::RectF( // the rect to draw in
		(float)targetSize.width / 2.0f - 600.0f,
										  (float)targetSize.height / 2.0f - 300.0f,
										  (float)targetSize.width / 2.0f + 600.0f,
										  (float)targetSize.height / 2.0f + 000.0f
	);

	Window::GFX().GetContext2D()->FillRectangle( &rect, pWBackgroundBrush.Get() );
	Window::GFX().GetContext2D()->DrawTextW(
		L"Draw", 4ui32,
		pBigTextFormat.Get(),
		&rect, pBTextBrush.Get() );

}


