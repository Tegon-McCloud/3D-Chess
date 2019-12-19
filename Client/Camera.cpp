#include "Camera.h"
#include "Util.h"

Camera::Camera( float x, float y, float z, float pitch, float yaw, float roll )
	: x( x ), y( y ), z( z ), pitch( pitch ), yaw( yaw ), roll( roll ) {}

void Camera::UpdateBuffer() {
	
	using namespace DirectX;

	XMVECTOR pos = XMVectorSet( x, y, z, 1.0f );
	XMVECTOR forward = XMVector3Transform( XMVectorSet( 0.0f, 0.0f, 1.0f, 0.0f ), XMMatrixRotationRollPitchYaw( pitch, yaw, roll ) );
	cameraTransforms.worldToCam = XMMatrixTranspose( XMMatrixLookAtRH( pos, pos + forward, XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f ) ) );
	cameraTransforms.proj = XMMatrixTranspose( XMMatrixPerspectiveFovRH( 1.5f, Window::Get().GetAspect(), 0.5f, 100.0f ) );

	buffer.Set( &cameraTransforms );
}

void Camera::Bind() {
	buffer.Bind();
}

void Camera::ToViewSpace( DirectX::XMVECTOR& v ) {
	using namespace DirectX;

}
