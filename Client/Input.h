#pragma once
#include <bitset>
#include <functional>
#include <vector>

class Input {

	void RegisterRightClickListener( std::function< void( int x, int y ) > onClick );
	bool IsKeyDown( char key ) const;

private:
	void RightClick();
	void KeyPressed( unsigned char key );
	void KeyReleased( unsigned char key );

	std::bitset< 256u > keyStates;
	std::vector< std::function< void( int x, int y ) > > onRightClick;


};

