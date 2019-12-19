#include "Input.h"

void Input::RegisterRightClickListener( std::function<void( int x, int y )> onClick ) {
	
}

void Input::RightClick() {

}

void Input::KeyPressed( unsigned char key ) {
	keyStates[key] = true;
}

void Input::KeyReleased( unsigned char key ) {
	keyStates[key] = false;
}
