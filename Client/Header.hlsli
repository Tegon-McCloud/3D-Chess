

typedef struct {
	float4 pos : SV_Position;
} VSOut, GSIn;

typedef struct {
	float4 pos : SV_POSITION;
	float3 col : Color;
} GSOut, PSIn ;
