#include "Drawable.h"
#include "Window.h"
#include "IndexBuffer.h"

void Drawable::Draw() {
	
	for ( std::unique_ptr<Bindable>& b : bindables ) {
		b->Bind();
	}

	Window::Get().GetGraphics().GetContext()->DrawIndexed( (UINT) indexCount, 0, 0 );
}

void Drawable::AddBindable( std::unique_ptr<Bindable> b ) {

	if ( IndexBuffer* ib = dynamic_cast<IndexBuffer*>(b.get()) ) {
		indexCount = ib->GetSize();
	}

	bindables.push_back( std::move( b ) );
}
