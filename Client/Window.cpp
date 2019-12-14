#include "Window.h"

#include <iostream>

// WindowsClass
WindowClass WindowClass::inst = WindowClass();

WindowClass::WindowClass() {

	WNDCLASSW wndCls = { 0 };

	wndCls.style = CS_DBLCLKS | CS_PARENTDC;
	wndCls.lpfnWndProc = (WNDPROC)(Window::Procedure);
	wndCls.cbClsExtra = 0;
	wndCls.cbWndExtra = 0;
	wndCls.hInstance = GetModuleHandle( NULL );
	wndCls.hIcon = NULL;
	wndCls.hCursor = LoadCursor( NULL, (LPTSTR)IDC_IBEAM );
	wndCls.hbrBackground = NULL;
	wndCls.lpszMenuName = NULL;
	wndCls.lpszClassName = wndClsName;
	
	if ( RegisterClassW( &wndCls ) == 0 ) {
		throw std::runtime_error( "Failed to register window class" );
	}

}

WindowClass::~WindowClass() {
	UnregisterClassW( wndClsName, GetModuleHandle( NULL ) );
}

// Window
Window::Window() {

	RECT wndRect = {};

	wndRect.left = 100;
	wndRect.right = wndRect.left + 1080;
	wndRect.top = 100;
	wndRect.bottom = wndRect.top + 720;

	AdjustWindowRect( &wndRect, WS_OVERLAPPEDWINDOW, FALSE );

	hWnd = CreateWindowExW(
		0,
		WindowClass::wndClsName,
		title,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, wndRect.right - wndRect.left, wndRect.bottom - wndRect.top,
		NULL,
		NULL,
		GetModuleHandle( NULL ),
		NULL
	);

	if ( hWnd == NULL ) {
		throw std::runtime_error("Failed to create window");
	}

	ShowWindow( hWnd, SW_SHOW );

	gfx = Graphics( hWnd, wndRect.right - wndRect.left, wndRect.bottom - wndRect.top );

}

HWND Window::GetHandle() const {
	return hWnd;
}

Graphics& Window::GetGraphics() {
	return gfx;
}

std::optional<int> Window::ProcessMessages() const {
	
	MSG msg;

	while ( PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE) ) {

		if ( msg.message == WM_QUIT ) {
			return (int) msg.wParam;
		}

		DispatchMessageW( &msg );
		TranslateMessage( &msg );

	}

	return std::optional<int>();

}

Window::operator HWND() const {
	return hWnd;
}

LRESULT CALLBACK Window::Procedure( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ) {

	switch ( message ) {
	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;
	default:
		return DefWindowProcW( hWnd, message, wParam, lParam );
	}

	return 0;
}
