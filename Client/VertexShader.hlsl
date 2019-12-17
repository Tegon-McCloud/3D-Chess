#include "Header.hlsli"

struct Vertex {
	float3 pos : Position;
};

cbuffer Model : register(b0) {
	matrix modelToWorld;
};

cbuffer Camera : register(b1) {
	matrix worldToCam;
	matrix proj;
}

VSOut main( Vertex v ) {

	VSOut output;

	output.viewPos = mul( mul( float4(v.pos, 1.0f), modelToWorld ), worldToCam );
	output.pos = mul( output.viewPos, proj );



	return output;
}
