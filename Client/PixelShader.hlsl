#include "Header.hlsli"

static const float3 lightDir = normalize(float3( 1.0f, -1.0f, 1.0f ));

cbuffer Material : register(b0) {
	float ambient_intensity;

	float3 diffuse_rgb;

	float specular_intensity;
	float specular_shininess;
}


float3 colAmbient() {
	return ambient_intensity * diffuse_rgb;
}

float3 colDiffuse( float3 normal ) {
	return diffuse_rgb * max(dot( -lightDir, normal ), 0.0f);
}

float4 main( PSIn input ) : SV_TARGET{

	input.normal = normalize( input.normal );

	return float4(colAmbient() + colDiffuse( input.normal ), 1.0f);
}
