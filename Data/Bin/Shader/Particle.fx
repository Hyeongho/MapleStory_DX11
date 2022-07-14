
#include "ShaderInfo.fx"

cbuffer	ParticleCBuffer : register(b11)
{
	uint g_ParticleSpawnEnable; // 파티클 생성여부
	float3 g_ParticleStartMin; // 파티클이 생성될 영역의 Min
	float3 g_ParticleStartMax; // 파티클이 생성될 영역의 Max
	uint g_ParticleSpawnCountMax; // 생성될 파티클의 최대
	float3 g_ParticleScaleMin; // 생성될 파티클 크기의 Min
	float g_ParticleLifeTimeMin; // 생성될 파티클이 살아있을 최소시간
	float3 g_ParticleScaleMax; // 새성될 파티클 크기의 Max
	float g_ParticleLifeTimeMax; // 생성될 파티클이 살아있을 최대시간
	float4 g_ParticleColorMin; // 생성될 파티클의 색상 Min
	float4 g_ParticleColorMax; // 생성될 파티클의 색상 Max
	float g_ParticleSpeedMin; // 파티클의 최소 이동속도
	float g_ParticleSpeedMax; // 파티클의 최대 이동속도
	int g_ParticleMove; // 이동을 하는지 안하는지
	int g_ParticleGravity; // 중력 적용을 받는지 안받는지
	float3 g_ParticleMoveDir; // 이동을 한다면 기준이 될 이동 방향
	int g_Particle2D; // 2D용 파티클인지
	float3 g_ParticleMoveAngle; // 이동을 한다면 기준이 될 방향으로부터 x, y, z 에 저장된 각도만큼 틀어진 랜덤한 방향을 구한다.
	float g_ParticleEmpty;
};

#define	GRAVITY	9.8f

struct ParticleInfo
{
	float3 WorldPos;
	float3 Dir;
	float Speed;
	float LifeTime;
	float LifeTimeMax;
	int Alive;
	float FallTime;
	float FallStartY;
};

struct ParticleInfoShared
{
	uint SpawnEnable;

	float3 ScaleMin;
	float3 ScaleMax;

	float4 ColorMin;
	float4 ColorMax;

	int	 GravityEnable;
};

RWStructuredBuffer<ParticleInfo>		g_ParticleArray	: register(u0);
RWStructuredBuffer<ParticleInfoShared>	g_ParticleShare	: register(u1);

float3x3 ComputeRotationMatrix(float3 Angle)
{
	float3 ConvertAngle;
	ConvertAngle.x = DegreeToRadian(Angle.x);
	ConvertAngle.y = DegreeToRadian(Angle.y);
	ConvertAngle.z = DegreeToRadian(Angle.z);

	float3x3 matRotX, matRotY, matRotZ, matRot;

	// 11, 12, 13
	// 21, 22, 23
	// 31, 32, 33
	matRotX._11 = 1.f;
	matRotX._21 = 0.f;
	matRotX._31 = 0.f;

	matRotX._12 = 0.f;
	matRotX._22 = cos(ConvertAngle.x);
	matRotX._32 = -sin(ConvertAngle.x);

	matRotX._13 = 0.f;
	matRotX._23 = sin(ConvertAngle.x);
	matRotX._33 = cos(ConvertAngle.x);


	matRotY._11 = cos(ConvertAngle.y);
	matRotY._21 = 0.f;
	matRotY._31 = -sin(ConvertAngle.y);

	matRotY._12 = 0.f;
	matRotY._22 = 1.f;
	matRotY._32 = 0.f;

	matRotY._13 = sin(ConvertAngle.y);
	matRotY._23 = 0.f;
	matRotY._33 = cos(ConvertAngle.y);

	matRotZ._11 = cos(ConvertAngle.z);
	matRotZ._21 = -sin(ConvertAngle.z);
	matRotZ._31 = 0.f;

	matRotZ._12 = sin(ConvertAngle.z);
	matRotZ._22 = cos(ConvertAngle.z);
	matRotZ._32 = 0.f;

	matRotZ._13 = 0.f;
	matRotZ._23 = 0.f;
	matRotZ._33 = 1.f;

	matRot = mul(matRotX, matRotY);
	matRot = mul(matRot, matRotZ);

	return matRot;
}

[numthreads(64, 1, 1)]	// 스레드 그룹 스레드 수를 지정한다.
void ParticleUpdate(uint3 ThreadID : SV_DispatchThreadID)
{
	g_ParticleShare[0].SpawnEnable = g_ParticleSpawnEnable;
	g_ParticleShare[0].ScaleMin = g_ParticleScaleMin;
	g_ParticleShare[0].ScaleMax = g_ParticleScaleMax;
	g_ParticleShare[0].ColorMin = g_ParticleColorMin;
	g_ParticleShare[0].ColorMax = g_ParticleColorMax;
	g_ParticleShare[0].GravityEnable = g_ParticleGravity;

	// 동작되는 스레드의 수가 생성되는 파티클의 최대 수 보다 크거나 같다면
	// 잘못된 인덱스로 동작하기 때문에 처리를 안해준다.
	if (g_ParticleSpawnCountMax <= ThreadID.x)
	{
		return;
	}

	// 파티클이 살아있는 파티클인지 판단한다.
	if (g_ParticleArray[ThreadID.x].Alive == 0)
	{
		int	SpawnEnable = g_ParticleShare[0].SpawnEnable;
		int	Exchange = 0;

		if (g_ParticleShare[0].SpawnEnable == 1)
		{
			int	InputValue = SpawnEnable - 1;

			// 함수의 인자는 in, in, out으로 구성되어 있다.
			// in은 일반적으로 변수의 값을 넘겨줄때 사용한다.
			// out은 반쪽짜리 레퍼런스처럼 결과값을 여기의 변수에 받아올때 사용한다.
			InterlockedExchange(g_ParticleShare[0].SpawnEnable, InputValue, Exchange);

			if (Exchange == SpawnEnable)
			{
				g_ParticleArray[ThreadID.x].Alive = 1;
			}
		}

		if (g_ParticleArray[ThreadID.x].Alive == 0)
		{
			return;
		}

		// 살려야 하는 파티클이라면 파티클 생성정보를 만들어낸다.
		float key = ThreadID.x / g_ParticleSpawnCountMax;

		float3 RandomPos = float3(Rand(key), Rand(2.142f), Rand(key * 3.f));
		float Rand = (RandomPos.x + RandomPos.y + RandomPos.z) / 3.f;

		float3 StartRange = g_ParticleStartMax - g_ParticleStartMin;

		g_ParticleArray[ThreadID.x].WorldPos = RandomPos * StartRange + g_ParticleStartMin;

		g_ParticleArray[ThreadID.x].FallTime = 0.f;
		g_ParticleArray[ThreadID.x].FallStartY = g_ParticleArray[ThreadID.x].WorldPos.y;

		g_ParticleArray[ThreadID.x].LifeTime = 0.f;
		g_ParticleArray[ThreadID.x].LifeTimeMax = Rand * (g_ParticleLifeTimeMax - g_ParticleLifeTimeMin) + g_ParticleLifeTimeMin;

		if (g_ParticleMove == 1)
		{
			float3 ConvertAngle = (RandomPos.xyz * 2.f - 1.f) * g_ParticleMoveAngle;

			float3x3 matRot = ComputeRotationMatrix(ConvertAngle);

			float3 Dir = normalize(mul(g_ParticleMoveDir, matRot));

			g_ParticleArray[ThreadID.x].Speed = Rand * (g_ParticleSpeedMax - g_ParticleSpeedMin) + g_ParticleSpeedMin;
			g_ParticleArray[ThreadID.x].Dir = normalize(Dir + g_ParticleMoveDir);
			g_ParticleArray[ThreadID.x].Dir = Dir;

			// 각도로 처리한다면 x, y, z 의 랜덤한 각도를 3개 얻어오고 기준 방향을 중심으로 회전된 행렬을 곱해서'
			// 회전된 방향을 구해주도록 한다.
		}
	}

	// 현재 생성이 되어 있는 파티클일 경우
	else
	{
		g_ParticleArray[ThreadID.x].LifeTime += g_DeltaTime;

		float3 MovePos = (float3)0.f;

		if (g_ParticleMove == 1)
		{
			g_ParticleArray[ThreadID.x].WorldPos += g_ParticleArray[ThreadID.x].Dir * g_ParticleArray[ThreadID.x].Speed * g_DeltaTime;
		}

		// 중력 적용
		if (g_ParticleShare[0].GravityEnable)
		{
			g_ParticleArray[ThreadID.x].FallTime += g_DeltaTime;

			float Velocity = 0.f;

			if (g_ParticleArray[ThreadID.x].Dir.y > 0.f)
			{
				Velocity = g_ParticleArray[ThreadID.x].Speed * g_ParticleArray[ThreadID.x].FallTime;
			}

			g_ParticleArray[ThreadID.x].WorldPos.y = g_ParticleArray[ThreadID.x].FallStartY +
				(Velocity - 0.5f * GRAVITY * g_ParticleArray[ThreadID.x].FallTime * g_ParticleArray[ThreadID.x].FallTime * 10.f);

			g_ParticleArray[ThreadID.x].WorldPos.x += MovePos.x;
			g_ParticleArray[ThreadID.x].WorldPos.z += MovePos.z;
		}

		else
		{
			g_ParticleArray[ThreadID.x].WorldPos += MovePos;
		}

		if (g_ParticleArray[ThreadID.x].LifeTime >= g_ParticleArray[ThreadID.x].LifeTimeMax)
		{
			g_ParticleArray[ThreadID.x].Alive = 0;
		}
	}
}

struct VertexParticle
{
	float3 Pos : POSITION;
	uint InstanceID : SV_InstanceID; // 정점버퍼에 만들어서 넣어주는것이 아니다.
};

struct VertexParticleOutput
{
	uint InstanceID : TEXCOORD;
};

StructuredBuffer<ParticleInfo>		g_ParticleArraySRV	: register(t30);
StructuredBuffer<ParticleInfoShared>	g_ParticleShareSRV	: register(t31);

VertexParticleOutput ParticleVS(VertexParticle input)
{
	VertexParticleOutput output = (VertexParticleOutput)0;

	output.InstanceID = input.InstanceID;

	return output;
}

struct GeometryParticleOutput
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
	float2 UV : TEXCOORD;
	float4 ProjPos : POSITION;
};

static float3 g_ParticleLocalPos[4] =
{
	{-0.5f, 0.5f, 0.f},
	{0.5f, 0.5f, 0.f},
	{-0.5f, -0.5f, 0.f},
	{0.5f, -0.5f, 0.f}
};

// in : 값을 함수 안으로 넘겨줄때
// out : 함수안에서 결과를 넘겨받을때. 단 함수 안에서 이 값을 사용한 연산은 할 수 없다.
// inout : 그냥 레퍼런스.
[maxvertexcount(6)]
void ParticleGS(point VertexParticleOutput input[1], inout TriangleStream<GeometryParticleOutput> output)
{
	// 점을 사각형으로 확장한다.
	uint InstanceID = input[0].InstanceID;

	if (g_ParticleArraySRV[InstanceID].Alive == 0)
	{
		return;
	}

	GeometryParticleOutput	OutputArray[4] =
	{
		(GeometryParticleOutput)0.f,
		(GeometryParticleOutput)0.f,
		(GeometryParticleOutput)0.f,
		(GeometryParticleOutput)0.f
	};

	OutputArray[0].UV = float2(0.f, 0.f);
	OutputArray[1].UV = float2(1.f, 0.f);
	OutputArray[2].UV = float2(0.f, 1.f);
	OutputArray[3].UV = float2(1.f, 1.f);

	float Ratio = g_ParticleArraySRV[InstanceID].LifeTime / g_ParticleArraySRV[InstanceID].LifeTimeMax;

	float3	Scale = lerp(g_ParticleShareSRV[0].ScaleMin, g_ParticleShareSRV[0].ScaleMax, float3(Ratio, Ratio, Ratio));

	float4	Color = lerp(g_ParticleShareSRV[0].ColorMin, g_ParticleShareSRV[0].ColorMax, float4(Ratio, Ratio, Ratio, Ratio));

	// 4개의 최종 정점정보를 만들어준다.
	for (int i = 0; i < 4; ++i)
	{
		float3	WorldPos = g_ParticleArraySRV[InstanceID].WorldPos + g_ParticleLocalPos[i] * Scale;

		OutputArray[i].ProjPos = mul(float4(WorldPos, 1.f), g_matVP);
		OutputArray[i].Pos = OutputArray[i].ProjPos;
		OutputArray[i].Color = Color;
	}

	output.Append(OutputArray[0]);
	output.Append(OutputArray[1]);
	output.Append(OutputArray[3]);
	output.RestartStrip();

	output.Append(OutputArray[0]);
	output.Append(OutputArray[3]);
	output.Append(OutputArray[2]);
	output.RestartStrip();
}


PSOutput_Single ParticlePS(GeometryParticleOutput input)
{
	PSOutput_Single	output = (PSOutput_Single)0;

	float4 Color = g_BaseTexture.Sample(g_BaseSmp, input.UV);

	output.Color.rgb = Color.rgb * input.Color.rgb;

	if (Color.a == 0.f || input.Color.a == 0.f)
	{
		clip(-1);
	}

	output.Color.a = Color.a * input.Color.a;

	return output;
}