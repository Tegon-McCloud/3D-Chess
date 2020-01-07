#pragma once

#include "WRL.h"
#include "d2d1_1.h"
#include "dwrite_1.h"
#include <vector>
#include <string>

class MoveLog {

public:

	MoveLog();

	void Draw() const;

private:
	Microsoft::WRL::ComPtr<IDWriteTextFormat> pTextFormat;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pWTextBrush;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pWBackgroundBrush;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pBTextBrush;
	Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> pBBackgroundBrush;

	Microsoft::WRL::ComPtr<ID2D1Bitmap1> pLogImage;
	
	std::vector<std::wstring> moveLog;

};

