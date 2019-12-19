#include "Header.hlsli"

static const float3 lightDir = normalize(float3( 1.0f, -1.0f, 1.0f ));

cbuffer Material : register(b0) {
	float ambient_intensity;

	float3 diffuse_rgb;

	float specular_intensity;
	float specular_shininess;
}

cbuffer Light : register(b1) {
	float3 light_dir;
	float3 light_rgb;
}


inline float3 colAmbient() {
	return ambient_intensity * diffuse_rgb;
}

inline float3 colDiffuse( float3 normal ) {
	return diffuse_rgb * max( 0.0f, dot( -lightDir, normal ));
}

inline float3 reflect( float3 normal ) {
	return lightDir - 2.0f * normal * dot( lightDir, normal );

}

inline float3 colSpecular( float3 normal, float4 fragPos ) {
	return specular_intensity * pow( max( 0.0f, dot( reflect( normal ), normalize( -(float3)fragPos ) ) ), specular_shininess );
}

float4 main( PSIn input ) : SV_TARGET{

	input.normal = normalize( input.normal );

	return float4( saturate( colAmbient() + colDiffuse( input.normal ) + colSpecular( input.normal, input.viewPos ) ), 1.0f);
}
