#include "ShaderInfo.fx"

struct VertexPos
{
	// ���� �ڿ� : ���������̸� + ��ȣ �� �����Ѵ�.
	// ��ȣ�� �Ⱥ��̸� 0���� �����ȴ�.
	float3	Pos : POSITION;	// Vector3Ÿ��.
};

struct VertexPosOutput
{
	// SV�� ������ System Value�̴�. �� ���� �������Ϳ� ���常 �ϰ�
	// ������ ����ϸ� �ȵȴ�.
	float4	Pos : SV_POSITION;
};

cbuffer Collider : register(b11)
{
	float4	g_ColliderColor;
	matrix	g_matColliderWVP;
};

VertexPosOutput ColliderMeshVS(VertexPos input)
{
	VertexPosOutput	output = (VertexPosOutput)0;

	output.Pos = mul(float4(input.Pos, 1.f), g_matColliderWVP);

	return output;
}

PSOutput_Single ColliderMeshPS(VertexPosOutput input)
{
	PSOutput_Single	output = (PSOutput_Single)0;

	output.Color.rgb = g_ColliderColor.rgb;
	output.Color.a = g_ColliderColor.a;

	return output;
}

struct VertexUV
{
	// ���� �ڿ� : ���������̸� + ��ȣ �� �����Ѵ�.
	// ��ȣ�� �Ⱥ��̸� 0���� �����ȴ�.
	float3	Pos : POSITION;	// Vector3Ÿ��.
	float2	UV	: TEXCOORD;
};

struct VertexUVOutput
{
	// SV�� ������ System Value�̴�. �� ���� �������Ϳ� ���常 �ϰ�
	// ������ ����ϸ� �ȵȴ�.
	float4	Pos : SV_POSITION;
	float2	UV	: TEXCOORD;
};

VertexUVOutput ColliderPixelVS(VertexUV input)
{
	VertexUVOutput output = (VertexUVOutput)0;

	float3 Pos = input.Pos - float3(0.5f, 0.5f, 0.f) * float3(1.f, 1.f, 0.f);

	output.Pos = mul(float4(Pos, 1.f), g_matColliderWVP);
	output.UV = input.UV;

	return output;
}

PSOutput_Single ColliderPixelPS(VertexUVOutput input)
{
	PSOutput_Single	output = (PSOutput_Single)0;

	float4 BaseTextureColor = g_BaseTexture.Sample(g_BaseSmp, input.UV);

	output.Color.rgb = BaseTextureColor.rgb;

	if (BaseTextureColor.a == 0.f)
	{
		clip(-1);
	}

	output.Color.a = BaseTextureColor.a;

	return output;
}
