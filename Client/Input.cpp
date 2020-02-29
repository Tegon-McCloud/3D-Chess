#include "Input.h"
#include "Window.h"

Input::Input() : cursorVisible( false ) {}

Input::~Input() {
	if ( !cursorVisible ) {
		ShowCursor( TRUE );
	}
}

void Input::RegisterClickListener( const std::function<void( int x, int y )>& onClick ) const {
	onMouseClick.push_back( onClick );
}

void Input::RegisterMouseWheelListener( const std::function<void( int delta )>& onScroll ) const {
	onMouseWheel.push_back( onScroll );
}

void Input::RegisterKeyListener( unsigned char key, const std::function<void( bool )>& onKey ) const {
	this->onKey[key].push_back( onKey );
}

bool Input::IsKeyDown( unsigned char key ) const {
	return keyStates[key];
}

POINT Input::GetMousePos() const {
	POINT p;
	GetCursorPos( &p );
	ScreenToClient( Window::Get(), &p );
	return p;
}

void Input::CenterMouse() const {
	POINT p = { Window::Get().GetWidth() / 2, Window::Get().GetHeight() / 2 };
	ClientToScreen( Window::Get(), &p );
	SetCursorPos( p.x, p.y );
}

void Input::SetCursorVisible( bool visibility ) {
	if ( cursorVisible == visibility ) return;
	
	printf( "%i", ShowCursor( visibility ));
	cursorVisible = visibility;
}

void Input::MouseClick( POINTS p ) {
	for ( auto f : onMouseClick ) {
		f( p.x, p.y );
	}
}

void Input::WheelScroll( int rawDelta ) {
	rawDelta /= WHEEL_DELTA;
	for ( auto f : onMouseWheel ) {
		f( rawDelta );
	}
}

void Input::KeyPressed( unsigned char key ) {
	keyStates[key] = true;

	for ( auto& f : onKey[key] ) {
		f( true );
	}

}

void Input::KeyReleased( unsigned char key ) {
	keyStates[key] = false;

	for ( auto& f : onKey[key] ) {
		f( false );
	}
}

void Input::WindowFocused() {
	if ( !cursorVisible ) ShowCursor( false );
}

void Input::WindowUnfocused() {
	if( !cursorVisible) ShowCursor( true );
}
