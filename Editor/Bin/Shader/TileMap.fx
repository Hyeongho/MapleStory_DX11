#include "ShaderInfo.fx"

struct VertexUV
{
    // 변수 뒤에 : 레지스터이름 + 번호 로 지정한다.
    // 번호를 안붙이면 0으로 지정된다.
    float3 Pos : POSITION; // Vector3타입.
    float2 UV : TEXCOORD;
    uint InstanceID : SV_InstanceID;
};

struct VertexUVOutput
{
    // SV가 붙으면 System Value이다. 이 값은 레지스터에 저장만 하고
    // 가져다 사용하면 안된다.
    float4 Pos : SV_POSITION;
    float2 UV : TEXCOORD;
    float2 OriginUV : TEXCOORD1;
    float4 Color : COLOR;
    float Opacity : TEXCOORD2;
};

cbuffer Animation2D : register(b10)
{
    float2 g_Animation2DStartUV;
    float2 g_Animation2DEndUV;
    int g_Animation2DType;
    float3 g_Animation2DEmpty;
};

cbuffer TileMapCBuffer : register(b11)
{
    float2 g_TileImageSize;
    float2 g_TileSize;
    float2 g_TileStart;
    float2 g_TileEnd;
    matrix g_matTileWVP;
};

struct TileInfo
{
    matrix matWVP;
    float2 TileStart;
    float2 TileEnd;
    float4 TileColor;
    float Opacity;
    float3 Empty;
};

StructuredBuffer<TileInfo> g_TileArray : register(t40);


float2 ComputeTileUV(float2 UV, float2 TileStart, float2 TileEnd)
{
    float2 result = (float2) 0.f;

    if (UV.x == 0.f)
    {
        result.x = TileStart.x / g_TileImageSize.x;
    }

    else
    {
        result.x = TileEnd.x / g_TileImageSize.x;
    }

    if (UV.y == 0.f)
    {
        result.y = TileStart.y / g_TileImageSize.y;
    }

    else
    {
        result.y = TileEnd.y / g_TileImageSize.y;
    }

    return result;
}

float2 ComputeAnimation2DUV(float2 UV)
{
    float2 result = (float2) 0.f;

    if (UV.x == 0.f)
    {
        result.x = g_Animation2DStartUV.x;
    }

    else
    {
        result.x = g_Animation2DEndUV.x;
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

VertexUVOutput TileMapVS(VertexUV input)
{
    VertexUVOutput output = (VertexUVOutput)0;

    output.Pos = mul(float4(input.Pos, 1.f), g_TileArray[input.InstanceID].matWVP);

    if (g_Animation2DEnable == 0)
    {
        output.UV = ComputeTileUV(input.UV, g_TileArray[input.InstanceID].TileStart, g_TileArray[input.InstanceID].TileEnd);
    }

    else
    {
        output.UV = ComputeAnimation2DUV(input.UV);
    }

    output.OriginUV = input.UV;
    output.Color = g_TileArray[input.InstanceID].TileColor;
    output.Opacity = g_TileArray[input.InstanceID].Opacity;

    return output;
}

PSOutput_Single TileMapPS(VertexUVOutput input)
{
    PSOutput_Single output = (PSOutput_Single)0;

    float4 BaseTextureColor = g_BaseTexture.Sample(g_BaseSmp, input.UV);

    if (BaseTextureColor.a == 0.f || g_MtrlOpacity == 0.f)
    {
        clip(-1);
    }

    float4 Color = PaperBurn2D(float4(BaseTextureColor.rgb * g_MtrlBaseColor.rgb, BaseTextureColor.a), input.OriginUV);

    output.Color.rgb = Color.rgb * input.Color.rgb;

    output.Color.a = Color.a * input.Opacity;

    return output;
}
