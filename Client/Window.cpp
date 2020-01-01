#include "Window.h"

#include <stdexcept>

// Window
Window::Window() : width(1080), height(720), gfx(Create()) {}

HWND Window::GetHandle() const {
	return hWnd;
}

const Graphics& Window::GetGraphics() const {
	return gfx;
}

const Input& Window::GetInput() const {
	return input;
}

void Window::SetVisible( bool visible, bool maximized ) const {
	ShowWindow( hWnd, visible ? maximized ? SW_MAXIMIZE : SW_SHOW : SW_HIDE );
}

std::optional<int> Window::ProcessMessages() const {
	
	MSG msg;

	while ( PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE) ) {

		if ( msg.message == WM_QUIT ) {
			return (int) msg.wParam;
		}

		DispatchMessageW( &msg );
		//TranslateMessage( &msg );
	}

	return std::optional<int>();

}

int Window::GetWidth() const {
	return width;
}

int Window::GetHeight() const {
	return height;
}

float Window::GetAspect() const {
	return aspectRatio;
}

bool Window::IsInFocus() const {
	return focus;
}

Window::operator HWND() const {
	return hWnd;
}

void Window::SizeChanged( int width, int height ) {
	this->width = width;
	this->height = height;
	aspectRatio = (float)width / height;

	gfx.SizeChanged();
}

HWND Window::Create() {

	RECT wndRect = {};

	wndRect.left = 100;
	wndRect.right = wndRect.left + width;
	wndRect.top = 100;
	wndRect.bottom = wndRect.top + height;

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
		throw std::runtime_error( "Failed to create window" );
	}

	return hWnd;
}

LRESULT CALLBACK Window::Procedure( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam ) {

	switch ( message ) {
	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;


	case WM_CLOSE:
		PostQuitMessage( 0 );
		break;
		

	case WM_SIZE:
		if(wParam == SIZE_RESTORED || wParam == SIZE_MAXIMIZED) GetInternal().SizeChanged( LOWORD( lParam ), HIWORD( lParam ) );
		break;


	case WM_RBUTTONDOWN:
	case WM_LBUTTONDOWN:
		printf( "yay\n" );

		GetInternal().input.MouseClick( MAKEPOINTS(lParam) );
		break;
		

	case WM_KEYDOWN:
		GetInternal().input.KeyPressed( static_cast<unsigned char>(wParam) );
		break;
	case WM_KEYUP:
		GetInternal().input.KeyReleased( static_cast<unsigned char>(wParam) );
		break;


	case WM_SETFOCUS:
		GetInternal().input.WindowFocused();
		GetInternal().focus = true;
		break;
	
	
	case WM_KILLFOCUS:
		GetInternal().input.WindowUnfocused();
		GetInternal().focus = false;
		break;


	default:
		return DefWindowProcW( hWnd, message, wParam, lParam );
	}

	return 0;
}

// WindowsClass
WindowClass WindowClass::inst = WindowClass();

WindowClass::WindowClass() {

	WNDCLASSW wndCls = { 0 };

	wndCls.style = CS_PARENTDC;
	wndCls.lpfnWndProc = (WNDPROC)(Window::Procedure);
	wndCls.cbClsExtra = 0;
	wndCls.cbWndExtra = 0;
	wndCls.hInstance = GetModuleHandle( NULL );
	wndCls.hIcon = NULL;
	wndCls.hCursor = LoadCursor( NULL, (LPTSTR)IDC_ARROW );
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
