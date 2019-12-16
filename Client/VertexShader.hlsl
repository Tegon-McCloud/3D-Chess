#include "Header.hlsli"

struct Vertex {
	float3 pos : Position;
};

cbuffer Projection : register(b0) {
	matrix projection;
};

VSOut main( Vertex v ) {

	VSOut output;
	output.pos = mul( float4(v.pos, 1.0f), projection );

	return output;
}
