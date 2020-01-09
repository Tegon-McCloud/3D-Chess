#include "Drawable.h"
#include "Window.h"
#include "IndexBuffer.h"

#include "d3d11_2.h"

void Drawable::Draw() const {
	
	for ( const std::shared_ptr<Bindable>& b : bindables ) {
		b->Bind();
	}

	Window::Get().GetGraphics().GetContext()->DrawIndexed( (UINT) indexCount, 0, 0 );
}

void Drawable::AddBindable( const std::shared_ptr<Bindable>& b ) {

	if ( IndexBuffer* ib = dynamic_cast<IndexBuffer*>(b.get()) ) {
		indexCount = ib->GetSize();
	}

	bindables.push_back( b );
}
