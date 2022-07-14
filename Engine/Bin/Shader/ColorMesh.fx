#include "ShaderInfo.fx"

struct VertexColor
{
	// ���� �ڿ� : ���������̸� + ��ȣ �� �����Ѵ�.
	// ��ȣ�� �Ⱥ��̸� 0���� �����ȴ�.
	float3 Pos : POSITION;	// Vector3Ÿ��.
	float4 Color : COLOR;
};

struct VertexColorOutput
{
	// SV�� ������ System Value�̴�. �� ���� �������Ϳ� ���常 �ϰ�
	// ������ ����ϸ� �ȵȴ�.
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
	float2 OriginUV : TEXCOORD1;
};

VertexColorOutput ColorMeshVS(VertexColor input)
{
	VertexColorOutput output = (VertexColorOutput)0;

	float3	Pos = input.Pos - g_Pivot * g_MeshSize;

	output.Pos = mul(float4(Pos, 1.f), g_matWVP);
	output.Color = input.Color;

	if (input.Pos.x > 0.f)
	{
		output.OriginUV.x = 1.f;
	}

	else
	{
		output.OriginUV.x = 0.f;
	}

	if (input.Pos.y > 0.f)
	{
		output.OriginUV.y = 0.f;
	}

	else
	{
		output.OriginUV.y = 1.f;
	}

	return output;
}

PSOutput_Single ColorMeshPS(VertexColorOutput input)
{
	PSOutput_Single	output = (PSOutput_Single)0;

	float4	Color = PaperBurn2D(input.Color, input.OriginUV);

	output.Color = Color;

	return output;
}

struct VertexPos
{
	// ���� �ڿ� : ���������̸� + ��ȣ �� �����Ѵ�.
	// ��ȣ�� �Ⱥ��̸� 0���� �����ȴ�.
	float3 Pos : POSITION;	// Vector3Ÿ��.
};

struct VertexPosOutput
{
	// SV�� ������ System Value�̴�. �� ���� �������Ϳ� ���常 �ϰ�
	// ������ ����ϸ� �ȵȴ�.
	float4 Pos : SV_POSITION;
};

VertexPosOutput PosMeshVS(VertexPos input)
{
	VertexPosOutput	output = (VertexPosOutput)0;

	float3 Pos = input.Pos - g_Pivot * g_MeshSize;

	output.Pos = mul(float4(Pos, 1.f), g_matWVP);

	return output;
}

PSOutput_Single PosMeshPS(VertexPosOutput input)
{
	PSOutput_Single	output = (PSOutput_Single)0;

	output.Color.rgb = g_MtrlBaseColor.rgb;
	output.Color.a = g_MtrlOpacity;

	return output;
}