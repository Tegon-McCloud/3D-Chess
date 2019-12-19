#pragma once
#include <bitset>
#include <functional>
#include <vector>
#include "WindowsStrict.h"

class Input {

	friend class Window;

public:
	Input();
	~Input();
	
	void RegisterRightClickListener( const std::function< void( int x, int y ) >& onClick );
	bool IsKeyDown( unsigned char key ) const;
	POINT GetMousePos();
	void CenterMouse();
	void SetCursorVisible( bool visibility );

private:
	void MouseClick( int x, int y );
	void KeyPressed( unsigned char key );
	void KeyReleased( unsigned char key );
	void WindowFocused();
	void WindowUnfocused();

	std::bitset< 256u > keyStates;
	std::vector< std::function< void( int x, int y ) > > onMouseClick;
	bool cursorVisible;

};

