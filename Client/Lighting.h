#pragma once

#include "DirectXMath.h"

struct alignas(16) Light {
	DirectX::XMFLOAT3 dir;
	DirectX::XMFLOAT3 rgb;
};
