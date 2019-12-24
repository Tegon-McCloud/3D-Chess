#pragma once
#include "Drawable.h"
#include "ConstantBuffer.h"

#include "DirectXMath.h"
#include <memory>
#include <string>

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

	float transparency;

} Material;


class Model : public Drawable {

public:
	Model( const std::string& name, const Material& m );

	void Draw( const DirectX::XMMATRIX& transform );

private:
	std::shared_ptr< ConstantBuffer< DirectX::XMMATRIX, VS, 0u > > pTransformBuffer;
};
