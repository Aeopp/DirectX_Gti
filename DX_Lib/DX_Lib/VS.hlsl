// �������̴� 1
// ���� ���� ��ŭ ȣ��ȴ�.(��ȯ=float4)
// �������̴��� �ݵ�� ������ ��ġ(SV_POSITION)�� ��ȯ�ؾ� �Ѵ�.
void VS(in float3 in_position : POSITION,
		in float4 in_color : COLOR,
		in float2 in_text : TEXCOORD,
		out float4 out_position: SV_POSITION,
		out float4 out_color : COLOR0,
		out float2 out_text : TEXCOORD0)
{
	//pos.x = p.x * c.x  + p.y * -c.y;
	//pos.y = p.x * c.y  + p.y * c.x ;
	//pos.z = p.z;
	//pos.w = 1.0f;
	out_position = float4(in_position, 1.0f);
	out_color = in_color;
	out_text = in_text; 
}

