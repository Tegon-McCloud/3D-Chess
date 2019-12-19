

typedef struct {
	float4 pos : SV_POSITION;
	float4 viewPos : VIEW_POSITION;
} VSOut, GSIn;

typedef struct {
	float4 pos : SV_POSITION;
	float4 viewPos : VIEW_POSITION;
	nointerpolation float3 normal : NORMAL;
} GSOut, PSIn ;
