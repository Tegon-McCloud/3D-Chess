
#include "Windows_strict.h"
#include "Window.h"
#include <iostream>;

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd
) {

	std::optional<int> rv;

	while ( true ) {

		rv = Window::Get().ProcessMessages();
		if ( rv ) {
			return rv.value();
		}

	}

	return 0;
}

int main() {
	WinMain( NULL, NULL, NULL, 0 );
}
