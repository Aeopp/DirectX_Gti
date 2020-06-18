Texture2D text1 : register(t0);
Texture2D text2 : register(t1);
SamplerState pixelSample1 : register(s0);
cbuffer cb : register(b0)
{
	float4 Color : packoffset(c0);
	float xAdd : packoffset(c1.x);
	float yAdd : packoffset(c1.y);
	float fTime : packoffset(c1.w);
	float Angle : packoffset(c2.x);
}
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
};

float4 AlphaBlend(in  float4 p : SV_POSITION,
	in  float4 c : COLOR0,
	in  float2 t : TEXCOORD0) : SV_Target
{
	float4 color1 = text1.Sample(pixelSample1, t);
	float4 color2 = text2.Sample(pixelSample1, t);

	if (color1.r >= 1.0f &&
		color1.g <= 0.0f &&
		color1.b >= 1.0f) discard;

	float4 ret = float4(color1.r,
						color1.g,
						color1.b,
						1.f);
	return ret;
}

