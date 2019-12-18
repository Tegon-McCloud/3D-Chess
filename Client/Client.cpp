#include "Window.h"
#include <iostream>

#include "Model.h"
#include "Util.h"

#include "Camera.h"
#include "Shaders.h"
#include "Pieces.h"

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd ) {

	std::optional<int> rv;	// return value
	Window::Get().SetVisible( true );
	
	Timer timer;

	Pawn p( WHITE ); 
	
	Camera c( 0.0f, 2.0f, -4.0f, 0.1f, 0.0f, 0.0f );
	c.UpdateBuffer();
	c.Bind();

	VertexShader vs( "VertexShader" );
	vs.Bind();

	PixelShader ps( "PixelShader" );
	ps.Bind();
	
	GeometryShader gs( "GeometryShader" );
	gs.Bind();

	
	try {
		while ( true ) {
			float dt = timer.Time();
			timer.Reset();
			
			rv = Window::Get().ProcessMessages();
			if ( rv ) {
				return rv.value();
			}

			Window::Get().GetGraphics().Clear( 0.0f, 0.5f, 1.0f );
			c.UpdateBuffer();
			p.ApplyTransform( DirectX::XMMatrixRotationY( dt ) );
			p.Draw();
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
