#include "Camera.h"

Camera::Camera( float x, float y, float z, float pitch, float yaw, float roll )
	: x( x ), y( y ), z( z ), pitch( pitch ), yaw( yaw ), roll( roll ) {}

void Camera::UpdateBuffer() {
	
	using namespace DirectX;

	CameraTransforms transforms;
	XMVECTOR pos = XMVectorSet( x, y, z, 1.0f );
	XMVECTOR forward = XMVector3Transform( XMVectorSet( 0.0f, 0.0f, 1.0f, 0.0f ), XMMatrixRotationRollPitchYaw( pitch, yaw, roll ) );
	transforms.worldToCam = XMMatrixTranspose( XMMatrixLookAtLH( pos, pos + forward, XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f ) ) );
	transforms.proj = XMMatrixTranspose( XMMatrixPerspectiveFovLH( 1.57f, (float)Window::Get().GetWidth() / (float)Window::Get().GetHeight(), 0.5f, 100.0f ) );

	buffer.Set( &transforms );
}

void Camera::Bind() {
	buffer.Bind();
}
