#pragma once

#include "WindowsStrict.h"
#include "Graphics.h"
#include <optional>
#include "Input.h"

class Window {

	friend class WindowClass; // Give WindowClass access to the Procedure method

private:
	Window();

public:

	HWND GetHandle() const;
	const Graphics& GetGraphics();

	Input& GetInput();

	void SetVisible( bool visible, bool maximized = false );

	std::optional<int> ProcessMessages() const;

	int GetWidth() const;
	int GetHeight() const;
	bool IsInFocus() const;

	operator HWND() const;

	static Window& Get() { // Singleton getter
		static Window inst;
		return inst;
	}

private:
	
	// delete these so no one can copy the window instance
	Window(const Window& ) = delete;
	Window& operator=( const Window& ) = delete;

	void SizeChanged( int width, int height );
	HWND Create();

	static LRESULT CALLBACK Procedure( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
	
public:
	static constexpr const wchar_t title[] = L"3D-Chess";

private:
	int x, y, width, height;
	HWND hWnd;
	Graphics gfx;
	Input input;

};

class WindowClass {

public:
	static constexpr const wchar_t wndClsName[] = L"FunctionRenderWindowClass";

private:
	WindowClass();
	~WindowClass();

private:
	static WindowClass inst;

};
