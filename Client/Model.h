#pragma once
#include "Drawable.h"
#include "ConstantBuffer.h"

#include "DirectXMath.h"
#include <memory>
#include <string>

typedef struct alignas(16) {
	struct {
		float r, g, b;
	} color;

	 struct {
		float intensity;
	} ambient;

	struct {
		float intensity;
	} diffuse;
	
	struct {
		float intensity, shininess;
	} specular;

	float transparency;

} Material;


class Model : public Drawable {

public:
	Model( const std::string& name, const Material& m );

	void Draw( const DirectX::XMMATRIX& transform );
	void SetMaterial( const Material& mtl );

private:
	std::shared_ptr< ConstantBuffer< DirectX::XMMATRIX, VS, 0u > > pTransformBuffer;
	std::shared_ptr< ConstantBuffer< Material, PS, 0u > > pMaterialBuffer;
};
