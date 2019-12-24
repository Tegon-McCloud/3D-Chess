#include "Header2D.hlsli"

struct Vertex {
	float3 pos : POSITION;
	float2 tc : TEXCOORD; 
};

VSOut main( Vertex v ) {
	VSOut output;
	output.pos = float4(v.pos, 1.0f);
	output.tc = v.tc;
	return output;
}