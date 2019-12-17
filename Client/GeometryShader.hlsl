#include "Header.hlsli"

[maxvertexcount(3)]
void main( triangle GSIn input[3] : SV_POSITION, inout TriangleStream< GSOut > output ) {

	GSOut element;

	// find normal by crossing 3D components of two edges.
	float3 normal = cross( (float3)(input[1].viewPos - input[0].viewPos), (float3)(input[2].viewPos - input[0].viewPos) );
	
	element.pos = input[0].pos;
	element.normal = normal;
	output.Append( element );

	element.pos = input[1].pos;
	output.Append( element );

	element.pos = input[2].pos;
	output.Append( element );

}