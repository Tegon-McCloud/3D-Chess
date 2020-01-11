#pragma once

#include "WindowsStrict.h"

#include <bitset>
#include <vector>
#include <functional>

class Input {

	friend class Window;

public:
	Input();
	~Input();
	
	void RegisterClickListener( const std::function< void( int x, int y ) >& onClick ) const;
	void RegisterMouseWheelListener( const std::function< void( int delta ) >& onScroll ) const;
	bool IsKeyDown( unsigned char key ) const;
	POINT GetMousePos() const;
	void CenterMouse() const;
	void SetCursorVisible( bool visibility );

private:
	void MouseClick( POINTS p );
	void WheelScroll( int rawDelta );
	void KeyPressed( unsigned char key );
	void KeyReleased( unsigned char key );
	void WindowFocused();
	void WindowUnfocused();

	std::bitset< 256u > keyStates;
	mutable std::vector<std::function<void( int x, int y )>> onMouseClick;
	mutable std::vector<std::function<void( int delta )>> onMouseWheel;
	bool cursorVisible;

};

