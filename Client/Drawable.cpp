#include "Drawable.h"
#include "Window.h"
#include "IndexBuffer.h"

void Drawable::Draw() {
	
	for ( std::unique_ptr<Bindable>& b : bindables ) {
		b->Bind();
	}

	Window::Get().GetGraphics().GetContext()->DrawIndexed( indexCount, 0, 0 );
}

void Drawable::AddBindable( std::unique_ptr<Bindable> b ) {

	bindables.push_back( std::move( b ) );

	if ( const IndexBuffer* ib = dynamic_cast<const IndexBuffer*>(b.get()) ) {
		indexCount = ib->GetSize();
	}

}
