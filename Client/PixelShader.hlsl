#include "Header.hlsli"

static const float3 lightDir = normalize(float3( 1.0f, -1.0f, 1.0f ));

cbuffer Material : register(b0) {
	struct {
		float intensity;
	} ambient;

	struct {
		float3 rgb;
	} diffuse;

	struct {
		float intensity, shininess;
	} specular;

	float padding[2];
}


float3 colAmbient() {
	return ambient.intensity * diffuse.rgb;
}

float3 colDiffuse( float3 normal ) {
	return diffuse.rgb * max(dot( -lightDir, normal ), 0.0f);
}

float4 main( PSIn input ) : SV_TARGET{

	input.normal = normalize( input.normal );

	return float4(ambient.intensity * diffuse.rgb + diffuse.rgb * max( dot( -lightDir, input.normal ), 0.0f ), 1.0f);
}
