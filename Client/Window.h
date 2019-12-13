#pragma once

#include "Windows_strict.h"
#include <optional>

class Window {

	friend class WindowClass; // Give WindowClass access to the Procedure method

private:
	Window();

public:

	HWND GetHandle() const;
	std::optional<int> ProcessMessages() const;

	static const Window& Get() { // Singleton getter
		static Window inst;
		return inst;
	}

private:
	
	// delete these so no one can copy the window instance
	Window(const Window& ) = delete;
	Window& operator=( const Window& ) = delete;

	static LRESULT CALLBACK Procedure( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
	
public:
	static constexpr const wchar_t title[] = L"3D-Chess";

private:
	HWND hWnd;


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
