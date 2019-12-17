#include "Header.hlsli"

static const float3 matCol = float3(0.5f, 0.5f, 0.5f);
static const float3 lightDir = normalize( float3(1.0f, -1.0f, 0.0f) );

float3 diffuse( float3 normal ) {
	return matCol * dot( -lightDir, normal );
}

float4 main( PSIn input ) : SV_TARGET{

	input.normal = normalize( input.normal );

	return float4(diffuse( input.normal ), 1.0f);
}
