#pragma once
#include "Drawable.h"
#include <string>
#include "ConstantBuffer.h"
#include "DirectXMath.h"

typedef struct alignas(16) {
	 struct {
		float intensity;
	} ambient;

	struct {
		float r, g, b;
	} diffuse;
	
	struct {
		float intensity, shininess;
	} specular;

} Material;


class Model : public Drawable {

public:
	Model( std::string name, DirectX::XMMATRIX baseTransform = DirectX::XMMatrixIdentity(), bool flipWinding = false );
	
	void ApplyTransform( DirectX::XMMATRIX transform );
	void SetTransform( DirectX::XMMATRIX transform );

private:

	DirectX::XMFLOAT4X4 transform;
	DirectX::XMFLOAT4X4 baseTransform;

	std::shared_ptr< ConstantBuffer< DirectX::XMMATRIX, VS, 0u > > pTransformBuffer;
	
};

