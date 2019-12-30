#include "Window.h"
#include <iostream>

#include "Util.h"
#include "Shaders.h"
#include "Chess.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd ) {

	using namespace DirectX;
	
	std::string cmdLine( lpCmdLine );

	std::optional<int> rv;	// return value
	
	Timer timer;

	Window::Get().SetVisible( true, true );

	Chess chess( cmdLine );

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
			
			chess.Update( dt );
			chess.Draw();

			Window::Get().GetGraphics().Present();

		}
	} catch ( std::runtime_error e ) {
		std::cout << "Application exited do to exception:\n" << e.what() << "\n";
	}

	return 0;
}

int main() {

	char cmdLine[] = "127.0.0.1:8877";
	return WinMain( GetModuleHandle( NULL ), NULL, cmdLine, 0 );
}
