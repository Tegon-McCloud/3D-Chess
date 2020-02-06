#pragma once
class Chess;

#include "Util.h"

#include "WRL.h"
#include "d2d1_1.h"
#include "dwrite_1.h"
#include <vector>
#include <string>

class MoveLog {

public:

	MoveLog();

	void Draw() const;
	void AddMove( const Chess& game, const PositionLFR& p1, const PositionLFR& p2 );

private:

	Microsoft::WRL::ComPtr<IDWriteTextFormat> pTextFormat;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pWTextBrush;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pWBackgroundBrush;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pBTextBrush;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pBBackgroundBrush;
	
	std::vector<std::wstring> moves;
	size_t scroll;

};
