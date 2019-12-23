#include "Camera.h"
#include "Util.h"

Camera::Camera( float x, float y, float z, float pitch, float yaw, float roll )
	: x( x ), y( y ), z( z ), pitch( pitch ), yaw( yaw ), roll( roll ) {}

void Camera::UpdateBuffer() {
	
	using namespace DirectX;

	XMVECTOR pos = XMVectorSet( x, y, z, 1.0f );
	XMVECTOR forward = XMVector3Transform( XMVectorSet( 0.0f, 0.0f, 1.0f, 0.0f ), XMMatrixRotationRollPitchYaw( pitch, yaw, roll ) );
	
	struct alignas(16) {
		XMMATRIX m1, m2;
	} matrices = {
		XMMatrixTranspose( XMMatrixLookAtRH( pos, pos + forward, XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f ) ) ),
		XMMatrixTranspose( XMMatrixPerspectiveFovRH( 1.5f, Window::Get().GetAspect(), 0.5f, 100.0f ) )
	};

	buffer.Set( reinterpret_cast< CameraTransforms* >( &matrices ) );
	
	XMStoreFloat4x4( &cameraTransforms.worldToCam, XMMatrixTranspose( matrices.m1 )  );
	XMStoreFloat4x4( &cameraTransforms.proj, XMMatrixTranspose( matrices.m2 ) );

}

void Camera::Bind() {
	buffer.Bind();
}

DirectX::XMVECTOR Camera::ToViewSpace3( const DirectX::XMVECTOR& v ) {
	using namespace DirectX;
	return  XMVector3Transform( v, XMLoadFloat4x4( &cameraTransforms.worldToCam ) );
}

DirectX::XMVECTOR Camera::ToViewSpace4( const DirectX::XMVECTOR& v ) {
	using namespace DirectX;
	return  XMVector4Transform( v, XMLoadFloat4x4( &cameraTransforms.worldToCam ) );
}
