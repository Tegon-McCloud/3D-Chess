#pragma once

#include "ConstantBuffer.h"

#include "DirectXMath.h"

typedef struct alignas(16) {
	DirectX::XMFLOAT3 dir;
	DirectX::XMFLOAT3 rgb;
} Light;
