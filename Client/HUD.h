#pragma once

#include "WRL.h"
#include "dwrite_1.h"
#include "d2d1_1.h"

#include <vector>
#include <string>

class HUD {

public:

	HUD();

	void DrawMoveLog( const std::vector<std::wstring>& moves ) const;

private:
	Microsoft::WRL::ComPtr<IDWriteTextFormat> pTextFormat;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pWTextBrush;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pWBackgroundBrush;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pBTextBrush;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pBBackgroundBrush;
	
};

