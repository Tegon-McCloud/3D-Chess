
#include "Window.h"
#include <iostream>

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd
) {

	std::optional<int> rv;	// return value

	Window::Get().SetVisible( true );

	try {
		while ( true ) {

			rv = Window::Get().ProcessMessages();
			if ( rv ) {
				return rv.value();
			}

			Window::Get().GetGraphics().Clear( 0.0f, 0.5f, 1.0f );
			Window::Get().GetGraphics().Present();

		}
	} catch ( std::runtime_error e ) {
		std::cout << "Application exiting do to exception:\n" << e.what() << "\n";
	}

	return 0;
}

int main() {
	WinMain( NULL, NULL, NULL, 0 );
}
