#include "Header.hlsli"

struct Vertex {
	float3 pos : POSITION;
};

cbuffer Model : register(b0) {
	matrix modelToWorld;
};

cbuffer Camera : register(b1) {
	matrix worldToView;
	matrix proj;
}

VSOut main( Vertex v ) {

	VSOut output;

	output.viewPos = mul( mul( float4(v.pos, 1.0f), modelToWorld ), worldToView );
	output.pos = mul( output.viewPos, proj );

	return output;
}
