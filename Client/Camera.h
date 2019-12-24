#pragma once
#include "ConstantBuffer.h"

#include "DirectXMath.h"

typedef struct alignas(16) {
	DirectX::XMFLOAT4X4 worldToCam;
	DirectX::XMFLOAT4X4 proj;
} CameraTransforms;

struct Ray {
	DirectX::XMFLOAT4 ori;
	DirectX::XMFLOAT4 dir;
};

class Camera {

public:
	Camera( float x, float y, float z, float yaw, float pitch, float roll );

	void UpdateBuffer();
	void Bind(); // sets this as the camera to use

	DirectX::XMVECTOR ToViewSpace3( const DirectX::XMVECTOR& v ); // converts v from worldspace to viewspace
	DirectX::XMVECTOR ToViewSpace4( const DirectX::XMVECTOR& v );

	Ray LookRay();

protected:
	float x, y, z, pitch, yaw, roll;
	ConstantBuffer< CameraTransforms, VS, 1u > buffer;

	// precalculated on buffer update:
	CameraTransforms cameraTransforms;
	Ray lookRay;
};

