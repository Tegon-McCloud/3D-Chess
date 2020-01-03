#pragma once
#include "ConstantBuffer.h"
#include "Util.h"

#include "DirectXMath.h"

struct alignas(16) CameraTransforms {
	DirectX::XMFLOAT4X4 worldToCam;
	DirectX::XMFLOAT4X4 proj;
};

class Camera {

public:
	Camera( float x, float y, float z, float yaw, float pitch, float roll );

	// update the GPU buffer which contains the camera transformations. Has to be called every frame the camera moves.
	void UpdateBuffer(); 
	// sets this as the camera to use
	void Bind();

	void SetPosition( float x, float y, float z );
	void SetDirection( float yaw, float pitch, float roll );

	// converts v from worldspace to viewspace as a direction or position vector
	DirectX::XMVECTOR ToViewSpace3( const DirectX::XMVECTOR& v ); 
	DirectX::XMVECTOR ToViewSpace4( const DirectX::XMVECTOR& v );

	// gets a reference to a Ray that is pointing directly foward from the camera
	const Ray& LookRay(); 

protected:
	float x, y, z, pitch, yaw, roll;
	ConstantBuffer<CameraTransforms, VS, 1u> buffer;

	// precalculated on each buffer update
	CameraTransforms cameraTransforms;
	Ray lookRay;
};

