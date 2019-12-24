
typedef struct {

	float4 pos : SV_POSITION;
	float2 tc : TEXCOORD0;
	
} VSOut, GSIn;

typedef struct {

	float4 pos : SV_POSITION;
	float2 tc : TEXCOORD0;

} GSOut, PSIn;