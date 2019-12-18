#pragma once
#include "ConstantBuffer.h"
#include "DirectXMath.h"

typedef struct alignas(16) {
	DirectX::XMMATRIX worldToCam;
	DirectX::XMMATRIX proj;
} CameraTransforms;

class Camera {

public:
	Camera( float x, float y, float z, float yaw, float pitch, float roll );

	void UpdateBuffer();
	void Bind();

private:

	float x, y, z, pitch, yaw, roll;
	ConstantBuffer< CameraTransforms, VS, 1u > buffer;
};

