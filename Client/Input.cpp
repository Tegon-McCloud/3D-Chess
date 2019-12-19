#include "Input.h"
#include "Window.h"

Input::Input() : cursorVisible( false ) {
	SetCursor( LoadCursorW( NULL, IDC_ARROW ) );
}

Input::~Input() {
	if ( !cursorVisible ) {
		ShowCursor( TRUE );
	}
}

void Input::RegisterRightClickListener( const std::function<void( int x, int y )>& onClick ) {
	onMouseClick.push_back( onClick );
}

bool Input::IsKeyDown( unsigned char key ) const {
	return keyStates[key];
}

POINT Input::GetMousePos() {
	POINT p;
	GetCursorPos( &p );
	ScreenToClient( Window::Get(), &p );
	return p;
}

void Input::CenterMouse() {
	POINT p = { Window::Get().GetWidth() / 2, Window::Get().GetHeight() / 2 };
	ClientToScreen( Window::Get(), &p );
	SetCursorPos( p.x, p.y );
}

void Input::SetCursorVisible( bool visibility ) {
	if ( cursorVisible == visibility ) return;
	
	printf( "%i", ShowCursor( visibility ));
	cursorVisible = visibility;
}

void Input::MouseClick( int x, int y ) {
	for ( auto f : onMouseClick ) {
		f( x, y );
	}
}

void Input::KeyPressed( unsigned char key ) {
	keyStates[key] = true;
}

void Input::KeyReleased( unsigned char key ) {
	keyStates[key] = false;
}

void Input::WindowFocused() {
	if ( !cursorVisible ) ShowCursor( false );
}

void Input::WindowUnfocused() {
	if( !cursorVisible) ShowCursor( true );
}
