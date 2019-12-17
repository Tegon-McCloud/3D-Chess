#pragma once
#include "Drawable.h"
#include <string>
#include "ConstantBuffer.h"
#include "DirectXMath.h"

class Model : public Drawable {

public:
	Model( std::string name, bool flipWinding = false );
	
	void ApplyTransform( DirectX::XMMATRIX transform );
	void SetTransform( DirectX::XMMATRIX transform );

private:

	DirectX::XMFLOAT4X4 transform;

	std::shared_ptr<ConstantBuffer< DirectX::XMMATRIX, VS, 0u >> pTransformBuffer;

};
