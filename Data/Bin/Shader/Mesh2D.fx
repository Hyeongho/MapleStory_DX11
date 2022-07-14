#include "ShaderInfo.fx"

struct VertexUV
{
	// 변수 뒤에 : 레지스터이름 + 번호 로 지정한다.
	// 번호를 안붙이면 0으로 지정된다.
	float3 Pos : POSITION; // Vector3타입.
	float2 UV : TEXCOORD;
};

struct VertexUVOutput
{
	// SV가 붙으면 System Value이다. 이 값은 레지스터에 저장만 하고
	// 가져다 사용하면 안된다.
	float4 Pos : SV_POSITION;
	float2 UV : TEXCOORD;
	float2 OriginUV : TEXCOORD1;
};

cbuffer Animation2D	: register(b10)
{
	float2 g_Animation2DStartUV;
	float2 g_Animation2DEndUV;
	int g_AnimFlip;
	int g_Animation2DType;
	float3 g_Animation2DEmpty;
	float3 g_Empty;
};

#define	TextureAtlas 0
#define	TextureFrame 1
#define	TextureArray 2

float2 ComputeAnimation2DUV(float2 UV)
{
	float2 result = (float2)0.f;

	if (UV.x == 0.f)
	{
		if (g_AnimFlip == 0)
		{
			result.x = g_Animation2DEndUV.x;
		}

		else
		{
			result.x = g_Animation2DStartUV.x;
		}

		//result.x = g_Animation2DStartUV.x;
	}

	else
	{
		if (g_AnimFlip == 0)
		{
			result.x = g_Animation2DStartUV.x;
		}

		else
		{
			result.x = g_Animation2DEndUV.x;
		}	

		//result.x = g_Animation2DEndUV.x;
	}

	if (UV.y == 0.f)
	{
		result.y = g_Animation2DStartUV.y;
	}

	else
	{
		result.y = g_Animation2DEndUV.y;
	}

	return result;
}

VertexUVOutput Mesh2DVS(VertexUV input)
{
	VertexUVOutput output = (VertexUVOutput)0;

	float3 Pos = input.Pos - g_Pivot * g_MeshSize;

	output.Pos = mul(float4(Pos, 1.f), g_matWVP);

	if (g_Animation2DEnable == 0)
	{
		output.UV = input.UV;
	}

	else
	{
		output.UV = ComputeAnimation2DUV(input.UV);
	}

	if (g_MeshFlip == 0)
	{
		output.UV.x = 1.0f - output.UV.x;
	}

	return output;
}

PSOutput_Single Mesh2DPS(VertexUVOutput input)
{
	PSOutput_Single	output = (PSOutput_Single)0;

	float4	BaseTextureColor = g_BaseTexture.Sample(g_BaseSmp, input.UV);

	if (BaseTextureColor.a == 0.f || g_MtrlOpacity == 0.f)
	{
		clip(-1);
	}

	float4	Color = PaperBurn2D(float4(BaseTextureColor.rgb * g_MtrlBaseColor.rgb, BaseTextureColor.a), input.OriginUV);

	output.Color = Color;

	output.Color.a = Color.a * g_MtrlOpacity;

	return output;
}
