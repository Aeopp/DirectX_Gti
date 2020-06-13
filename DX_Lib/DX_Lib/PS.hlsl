Texture2D text1 : register(t0);
Texture2D text2 : register(t1);

SamplerState pixelSample1 : register(s0);

// 픽쉘 개수만큼 호출된다.
void PS(in  float4 pos : SV_POSITION,
		in  float4 color : COLOR0,
		in  float2 text_coord : TEXCOORD0,
		out float4 target : SV_Target)
{
	float4 color1 = text1.Sample(pixelSample1, text_coord);

	if (color1.r >= 1.0f &&
		color1.g <= 0.0f &&
		color1.b >= 1.0f) discard;

	target = color1;
}