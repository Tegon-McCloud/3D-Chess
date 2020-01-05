#include "Window.h"
#include <iostream>

#include "Util.h"
#include "Shaders.h"
#include "Chess.h"



int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow ) {

	using namespace DirectX;

	std::string cmdLine( lpCmdLine );

	std::optional<int> rv;	// return value
	
	Timer timer; // for keeping track of how long has passed between frames

	Window::Get().SetVisible( true, true );

	Chess chess( cmdLine );

	VertexShader vs( "VS" );
	vs.Bind();

	PixelShader ps( "PS" );
	ps.Bind();
	
	GeometryShader gs( "GS" );
	gs.Bind();

	Window::GFX().SetBlendEnabled( false );
	Window::GFX().SetDepthEnabled( true );

	try {
		while ( true ) {
			float dt = timer.Time();
			timer.Reset();
			
			rv = Window::Get().ProcessMessages();
			if ( rv ) {
				return rv.value();
			}

			Window::GFX().Clear( 0.0f, 0.5f, 1.0f );
			
			chess.Update( dt );
			chess.Draw();

			
			Window::GFX().SetDepthEnabled( false );
			Window::GFX().SetBlendEnabled( true );

			Window::GFX().GetContext2D()->BeginDraw();

			chess.DrawHUD();

			Window::GFX().GetContext2D()->EndDraw();
			Window::GFX().SetDepthEnabled( true );
			Window::GFX().SetBlendEnabled( false );

			Window::GFX().Present();

		}
	} catch ( std::runtime_error e ) {
		std::cout << "Application exited do to exception:\n" << e.what() << "\n";
	}

	return 0;
}

int main() { // target is console for debug so while debugging execution will start here
	char cmdLine[] = "80.210.71.221:8877";
	return WinMain( GetModuleHandle( NULL ), NULL, cmdLine, 0 );
}
