#include "Window.h"
#include <iostream>

#include "Util.h"
#include "Shaders.h"
#include "Chess.h"
#include "Client.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd ) {

	using namespace DirectX;

	std::optional<int> rv;	// return value
	Window::Get().SetVisible( true, true );
	
	Timer timer;

	Chess c;

	VertexShader vs( "VertexShader" );
	vs.Bind();

	PixelShader ps( "PixelShader" );
	ps.Bind();
	
	GeometryShader gs( "GeometryShader" );
	gs.Bind();
	
	Window::Get().GetGraphics().SetBlendEnabled( false );
	Window::Get().GetGraphics().SetDepthEnabled( true );

	try {
		while ( true ) {
			float dt = timer.Time();
			timer.Reset();
			
			rv = Window::Get().ProcessMessages();
			if ( rv ) {
				return rv.value();
			}

			Window::Get().GetGraphics().Clear( 0.0f, 0.5f, 1.0f );
			
			c.Update( dt );
			c.Draw();

			Window::Get().GetGraphics().Present();

		}
	} catch ( std::runtime_error e ) {
		std::cout << "Application exited do to exception:\n" << e.what() << "\n";
	}

	return 0;
}

int main() {
	//return WinMain( NULL, NULL, NULL, 0 );

	Client c( "localhost", "8877" );

	c.SendMSG( "yay" );

	std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );

	std::string response;
	c.GetMSG( response );
	std::cout << response << "\n";

	return 0;
}
