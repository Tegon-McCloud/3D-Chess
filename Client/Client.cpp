#include "Window.h"
#include <iostream>

#include "Model.h"
#include "Util.h"

#include "IndexBuffer.h"

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd
) {

	std::optional<int> rv;	// return value
	Window::Get().SetVisible( true );
	
	Timer timer;

	Model m( "Unicorn" );
	
	const unsigned short i[]{
		1, 2, 3
	};
	IndexBuffer ib( i, 3, "yay" );

	try {
		while ( true ) {

			rv = Window::Get().ProcessMessages();
			if ( rv ) {
				return rv.value();
			}

			Window::Get().GetGraphics().Clear( 0.0f, 0.5f, 1.0f );
			Window::Get().GetGraphics().DrawTest( timer.Time() );
			m.SetTransform( DirectX::XMMatrixRotationY( timer.Time() * 0.5f ) );
			m.Draw();
			Window::Get().GetGraphics().Present();
		}
	} catch ( std::runtime_error e ) {
		std::cout << "Application exited do to exception:\n" << e.what() << "\n";
	}

	return 0;
}

int main() {

	return WinMain( NULL, NULL, NULL, 0 );
}
