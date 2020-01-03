#include "Camera.h"

Camera::Camera( float x, float y, float z, float pitch, float yaw, float roll )
	: x( x ), y( y ), z( z ), pitch( pitch ), yaw( yaw ), roll( roll ) {}

void Camera::UpdateBuffer() {
	
	using namespace DirectX;

	XMVECTOR pos = XMVectorSet( x, y, z, 1.0f );
	XMVECTOR forward = XMVector3Transform( XMVectorSet( 0.0f, 0.0f, 1.0f, 0.0f ), XMMatrixRotationRollPitchYaw( pitch, yaw, roll ) );
	
	XMStoreFloat3( &lookRay.ori, pos );
	XMStoreFloat3( &lookRay.dir, forward );

	struct alignas(16) {
		XMMATRIX m1, m2;
	} matrices = {
		XMMatrixTranspose( XMMatrixLookAtRH( pos, pos + forward, XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f ) ) ),
		XMMatrixTranspose( XMMatrixPerspectiveFovRH( 1.5f, Window::Get().GetAspect(), 0.5f, 50.0f ) )
	};

	buffer.Set( reinterpret_cast< CameraTransforms* >( &matrices ) );
	
	XMStoreFloat4x4( &cameraTransforms.worldToCam, XMMatrixTranspose( matrices.m1 )  );
	XMStoreFloat4x4( &cameraTransforms.proj, XMMatrixTranspose( matrices.m2 ) );

}

void Camera::Bind() {
	buffer.Bind();
}

void Camera::SetPosition( float x, float y, float z ) {
	this->x = x;
	this->y = y;
	this->z = z;
}

void Camera::SetDirection( float yaw, float pitch, float roll ) {
	this->yaw = yaw;
	this->pitch = pitch;
	this->roll = roll;
}

DirectX::XMVECTOR Camera::ToViewSpace3( const DirectX::XMVECTOR& v ) {
	using namespace DirectX;
	return  XMVector3Transform( v, XMLoadFloat4x4( &cameraTransforms.worldToCam ) );
}

DirectX::XMVECTOR Camera::ToViewSpace4( const DirectX::XMVECTOR& v ) {
	using namespace DirectX;
	return  XMVector4Transform( v, XMLoadFloat4x4( &cameraTransforms.worldToCam ) );
}

const Ray& Camera::LookRay() {
	return lookRay;
}
