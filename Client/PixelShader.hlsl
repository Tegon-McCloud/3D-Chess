#include "Header.hlsli"

cbuffer Material : register(b0) {
	float3 color;
	
	float ambient_intensity;

	float diffuse_intensity;

	float specular_intensity;
	float specular_shininess;

	float transparency;
}

cbuffer Light : register(b1) {
	float3 light_dir;
	float3 light_rgb;
}


inline float3 colAmbient() {
	return ambient_intensity * color;
}

inline float3 colDiffuse( float3 normal ) {
	return color * diffuse_intensity * max( 0.0f, dot( light_dir, normal ));
}

inline float3 reflect( float3 normal ) {
	return light_dir - 2.0f * normal * dot( light_dir, normal );
}

inline float3 colSpecular( float3 normal, float4 fragPos ) {
	return specular_intensity * pow( max( 0.0f, dot( reflect( normal ), normalize( -(float3)fragPos ) ) ), specular_shininess );
}

float4 main( PSIn input ) : SV_TARGET{

	input.normal = normalize( input.normal );

	return float4( saturate( colAmbient() + colDiffuse( input.normal ) + colSpecular( input.normal, input.viewPos ) ), 1.0f - transparency);
}
