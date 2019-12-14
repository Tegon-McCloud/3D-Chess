#pragma once

#include "WindowsStrict.h"
#include "Graphics.h"
#include <optional>

class Window {

	friend class WindowClass; // Give WindowClass access to the Procedure method

private:
	Window();

public:

	HWND GetHandle() const;
	Graphics& GetGraphics();

	std::optional<int> ProcessMessages() const;

	static Window& Get() { // Singleton getter
		static Window inst;
		return inst;
	}

	operator HWND() const;

private:
	
	// delete these so no one can copy the window instance
	Window(const Window& ) = delete;
	Window& operator=( const Window& ) = delete;

	static LRESULT CALLBACK Procedure( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
	
public:
	static constexpr const wchar_t title[] = L"3D-Chess";

private:
	HWND hWnd;
	Graphics gfx;

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
