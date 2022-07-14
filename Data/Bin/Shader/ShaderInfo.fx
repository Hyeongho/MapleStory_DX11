
struct PSOutput_Single
{
	float4 Color : SV_TARGET;
};

cbuffer Transform : register(b0)
{
	matrix g_matWorld;
	matrix g_matView;
	matrix g_matProj;
	matrix g_matWV;
	matrix g_matWVP;
	matrix g_matVP;
	float3 g_Pivot;
	int g_MeshFlip;
	float g_TransformEmpty1;
	float3 g_MeshSize;
	float g_TransformEmpty;
};

cbuffer Material : register(b1)
{
	float4 g_MtrlBaseColor;
	float g_MtrlOpacity;
	int g_MtrlPaperBurnEnable;
	float2 g_MtrlEmpty;
};

cbuffer Standard2D : register(b2)
{
	int g_Animation2DEnable;
	float3 g_Standard2DEmpty;
};

cbuffer	GlobalCBuffer : register(b3)
{
	float g_DeltaTime;
	float g_AccTime;
	float2 g_Resolution;
	float2 g_NoiseResolution;
	float2 g_GlobalEmpty;
};

cbuffer PaperBurnCBuffer : register(b4)
{
	float4 g_PaperBurnInLineColor;
	float4 g_PaperBurnOutLineColor;
	float4 g_PaperBurnCenterLineColor;
	float g_PaperBurnFilter;
	int g_PaperBurnInverse;
	float g_PaperBurnInFilter;
	float g_PaperBurnOutFilter;
	float g_PaperBurnCenterFilter;
	float3 g_PaperBurnEmpty;
};

SamplerState g_PointSmp : register(s0);
SamplerState g_LinearSmp : register(s1);
SamplerState g_AnisotropicSmp: register(s2);

SamplerState g_BaseSmp : register(s3);

Texture2D g_BaseTexture : register(t0);

Texture2D<float4> g_NoiseTexture : register(t100);
Texture2D g_PaperBurnTexture : register(t101);

StructuredBuffer<float>	g_RandBuffer : register(t90);

static float Gaussian5x5[25] =
{
	0.003765f, 0.015019f, 0.023792f, 0.015019f, 0.003765f,
	0.015019f, 0.059912f, 0.094907f, 0.059912f, 0.015019f,
	0.023792f, 0.094907f, 0.150342f, 0.094907f, 0.023792f,
	0.015019f, 0.059912f, 0.094907f, 0.059912f, 0.015019f,
	0.003765f, 0.015019f, 0.023792f, 0.015019f, 0.003765f
};

float GaussianSample(int2 UV, Texture2D Tex)
{
	float Output = 0.f;

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			int2 ConvertUV = UV + int2(j - 2, i - 2);

			if (ConvertUV.x < 0)
			{
				ConvertUV.x = 0;
			}

			else if (ConvertUV.x > g_NoiseResolution.x)
			{
				ConvertUV.x = g_NoiseResolution.x - 1;
			}

			if (ConvertUV.y < 0)
			{
				ConvertUV.y = 0;
			}

			else if (ConvertUV.y > g_NoiseResolution.y)
			{
				ConvertUV.y = g_NoiseResolution.y - 1;
			}

			Output += Tex[ConvertUV].r * Gaussian5x5[i * 5 + j];
		}
	}

	return Output;
}

float Rand(float Key)
{
	float2	UV = float2(cos(Key + g_AccTime), sin(g_AccTime));

	UV = frac(UV);

	return GaussianSample(UV * g_NoiseResolution, g_NoiseTexture);
}

float DegreeToRadian(float Angle)
{
	return Angle / 180.f * 3.14159f;
}

float4 PaperBurn2D(float4 Color, float2 UV)
{
	if (g_MtrlPaperBurnEnable == 0)
	{
		return Color;
	}

	else if (Color.a == 0.f)
	{
		return Color;
	}

	float4 BurnColor = g_PaperBurnTexture.Sample(g_LinearSmp, UV);

	float4 result = Color;

	if (g_PaperBurnInverse == 0)
	{
		if (g_PaperBurnFilter >= BurnColor.r)
		{
			result.a = 0.f;
		}

		else
		{
			if (g_PaperBurnFilter - g_PaperBurnOutFilter <= BurnColor.r && BurnColor.r <= g_PaperBurnFilter + g_PaperBurnOutFilter)
			{
				result = g_PaperBurnOutLineColor;
			}

			if (g_PaperBurnFilter - g_PaperBurnCenterFilter <= BurnColor.r && BurnColor.r <= g_PaperBurnFilter + g_PaperBurnCenterFilter)
			{
				result = g_PaperBurnCenterLineColor;
			}

			if (g_PaperBurnFilter - g_PaperBurnInFilter <= BurnColor.r && BurnColor.r <= g_PaperBurnFilter + g_PaperBurnInFilter)
			{
				result = g_PaperBurnInLineColor;
			}
		}
	}

	else
	{
		if (g_PaperBurnFilter < BurnColor.r)
		{
			result.a = 0.f;
		}

		else
		{
			if (g_PaperBurnFilter - g_PaperBurnOutFilter <= BurnColor.r && BurnColor.r <= g_PaperBurnFilter + g_PaperBurnOutFilter)
			{
				result = g_PaperBurnOutLineColor;
			}

			if (g_PaperBurnFilter - g_PaperBurnCenterFilter <= BurnColor.r && BurnColor.r <= g_PaperBurnFilter + g_PaperBurnCenterFilter)
			{
				result = g_PaperBurnCenterLineColor;
			}

			if (g_PaperBurnFilter - g_PaperBurnInFilter <= BurnColor.r && BurnColor.r <= g_PaperBurnFilter + g_PaperBurnInFilter)
			{
				result = g_PaperBurnInLineColor;
			}
		}
	}

	result.a *= Color.a;

	return result;
}