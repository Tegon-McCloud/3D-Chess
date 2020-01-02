#include "Header.hlsli"

[maxvertexcount(3)]
void main( triangle GSIn input[3] : SV_POSITION, inout TriangleStream<GSOut> output ) {

	GSOut element;

	// find normal by crossing 3D components of two edges.
	// this could be precomputed, but it isn't worth it considering chess isn't the most heavy game to render
	float3 normal = cross( (float3)(input[1].viewPos - input[0].viewPos), (float3)(input[2].viewPos - input[0].viewPos) );
	
	element.pos = input[0].pos;
	element.viewPos = input[0].viewPos;
	element.normal = normal;
	output.Append( element );

	element.pos = input[1].pos;
	element.viewPos = input[1].viewPos;
	output.Append( element );

	element.pos = input[2].pos;
	element.viewPos = input[2].viewPos;
	output.Append( element );

}