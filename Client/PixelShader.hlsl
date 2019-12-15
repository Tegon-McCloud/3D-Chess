#include "Header.hlsli"

float4 main(PSIn input) : SV_TARGET {
	return input.col;
}
