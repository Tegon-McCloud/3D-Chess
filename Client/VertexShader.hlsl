#include "Header.hlsli"

struct Vertex {
	float2 pos : Position;
	float4 col : Color;
};

VSOut main( Vertex v ) {

	VSOut output;
	output.pos = float4(v.pos, 0.0f, 1.0f);
	output.col = v.col;

	return output;
}
