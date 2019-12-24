#include "Header2D.hlsli"

[maxvertexcount(3)]
void main( triangle GSIn input[3] : SV_POSITION, inout TriangleStream< GSOut > output ) {
	
	[unroll(3)]
	for (uint i = 0; i < 3; i++) {
		GSOut element;
		element.pos = input[i].pos;
		element.tc = input[i].tc;
		output.Append(element);
	}
}