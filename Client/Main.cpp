#include "Window.h"
#include <iostream>

#include "Util.h"
#include "Shaders.h"
#include "Chess.h"



int WINAPI WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow ) {

	std::string cmdLine( lpCmdLine );

	std::optional<int> rv;	// return value
	
	Timer timer; // for keeping track of how long has passed between frames
	const Timer constTimer;

	Window::Get().SetVisible( true, true );
	
	Chess chess( cmdLine );

	VertexShader vs( "VS" );
	vs.Bind();

	PixelShader ps( "PS" );
	ps.Bind();
	
	GeometryShader gs( "GS" );
	gs.Bind();

	Window::GFX().SetBlendEnabled( true );
	Window::GFX().SetDepthEnabled( true );

	while ( true ) {
		float dt = timer.Time();
		timer.Reset();
			
		rv = Window::Get().ProcessMessages();
		if ( rv ) {
			return rv.value();
		}
		
		Window::GFX().Clear( 0.2f, 0.4f, 0.8f );
			
		chess.Update( dt );
		chess.Draw();

		Window::GFX().SetDepthEnabled( false );
		Window::GFX().GetContext2D()->BeginDraw();

		chess.DrawHUD();

		Window::GFX().GetContext2D()->EndDraw();
		Window::GFX().SetDepthEnabled( true );

		Window::GFX().Present();

	}

	return 0;
}

int main() { // vs project buildtarget is console for debug so while debugging execution will start here
	char cmdLine[] = "80.210.71.221:8877";
	return WinMain( GetModuleHandle( NULL ), NULL, cmdLine, 0 );
}
