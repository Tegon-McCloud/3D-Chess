#include "Header.hlsli"

float4 main( PSIn input ) : SV_TARGET{
	return float4(input.col, 1.0f);
}
