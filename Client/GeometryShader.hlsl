#include "Header.hlsli"

[maxvertexcount(3)]
void main( triangle float4 input[3] : SV_POSITION, inout TriangleStream< GSOut > output ) {

	GSOut element;

	element.pos = input[0];
	element.col = float3( 1.0f, 0.0f, 0.0f );
	output.Append( element );

	element.pos = input[1];
	element.col = float3(0.0f, 1.0f, 0.0f);
	output.Append( element );

	element.pos = input[2];
	element.col = float3(0.0f, 0.0f, 1.0f);
	output.Append( element );

}