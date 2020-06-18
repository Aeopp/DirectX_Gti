cbuffer cb : register(b0)
{
	float4 Color: packoffset(c0);
	float  xAdd : packoffset(c1.x);
	float  yAdd : packoffset(c1.y);
	float  zAdd : packoffset(c1.z);
	float  fTime : packoffset(c1.w);
	float4 Scale : packoffset(c2);
	float4 RenderSize :packoffset(c3);
	float4 ScreenSize :packoffset(c4);
	float4 AnimData    :packoffset(c5);
//	float Angle : packoffset(c2.a);
}
// 정점쉐이더 1
// 정점 개수 만큼 호출된다.(반환=float4)
// 정점쉐이더는 반드시 정점의 위치(SV_POSITION)를 반환해야 한다.

struct VS_IN
{
	float3 p : POSITION;
	float4 c : COLOR;
	float2 t : TEXCOORD;
	uint index : SV_VertexID;
};

struct VS_OUT
{
	float4 pos	: SV_POSITION;
	float4 color: COLOR0;
	float2 tex	: TEXCOORD0;
};
//VS_OUT VS32(VS_IN vIn)
//{
//	VS_OUT vOut;
//	float3 vSrc = vIn.p;
//	vSrc.x = vSrc.x * 0.5f;
//	vSrc.y = vSrc.y * 0.5f;
//	vOut.pos.x = vSrc.x * cos(fTime) + vSrc.y * -sin(fTime) + xAdd;
//	vOut.pos.y = vSrc.x * sin(fTime) + vSrc.y * cos(fTime) + yAdd;
//	vOut.pos.z = vSrc.z;
//	vOut.pos.w = 1.0f;
//	//vOut.pos = float4(vIn.p,1.0f);
//	vOut.color = vIn.c;
//	vOut.tex = vIn.t;
//	return vOut;
//};
VS_OUT VS(VS_IN vIn)
{
	VS_OUT vOut;
	vOut.pos = float4(vIn.p,1.f);
	vOut.pos.w = 1.0f;
	//vOut.pos = float4(vIn.p,1.0f);
	vOut.color = vIn.c;
	vOut.tex = vIn.t;
	vOut.pos.x += xAdd;
	vOut.pos.y += yAdd;
	
	float AnimTop = AnimData.r;
	float AnimBottom = AnimData.g;

	if (vIn.index == 0) {
		//vOut.tex = float2(AnimData.r,0);
		vOut.tex = float2(0, AnimTop);
	}
	else if (vIn.index == 1) {
		//vOut.tex = float2(AnimData.g,0);
		vOut.tex = float2(1, AnimTop);
	}
	else if (vIn.index == 2) {
		//vOut.tex = float2(AnimData.r, 1);
		vOut.tex = float2(0, AnimBottom);

	}
	else if (vIn.index == 3) {
		//vOut.tex = float2(AnimData.g,1);
		vOut.tex = float2(1, AnimBottom);
	}
	return vOut;
};
