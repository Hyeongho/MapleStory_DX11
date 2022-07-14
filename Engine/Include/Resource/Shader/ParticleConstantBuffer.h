#pragma once

#include "ConstantBufferBase.h"

class CParticleConstantBuffer :
	public CConstantBufferBase
{
public:
	CParticleConstantBuffer();
	CParticleConstantBuffer(const CParticleConstantBuffer& Buffer);
	virtual ~CParticleConstantBuffer();

protected:
	ParticleCBuffer	m_BufferData;

public:
	virtual bool Init();
	virtual void UpdateCBuffer();
	virtual CParticleConstantBuffer* Clone();

public:
	const Vector3& GetStartMin() const
	{
		return m_BufferData.StartMin;
	}

	const Vector3& GetStartMax() const
	{
		return m_BufferData.StartMax;
	}

	int GetSpawnCount() const
	{
		return m_BufferData.SpawnCountMax;
	}

public:
	void SetSpawnEnable(unsigned int Count)
	{
		m_BufferData.SpawnEnable = Count;
	}

	void SetStartMin(const Vector3& StartMin)
	{
		m_BufferData.StartMin = StartMin;
	}

	void SetStartMax(const Vector3& StartMax)
	{
		m_BufferData.StartMax = StartMax;
	}

	void SetSpawnCountMax(unsigned int Count)
	{
		m_BufferData.SpawnCountMax = Count;
	}

	void SetScaleMin(const Vector3& ScaleMin)
	{
		m_BufferData.ScaleMin = ScaleMin;
	}

	void SetScaleMax(const Vector3& ScaleMax)
	{
		m_BufferData.ScaleMax = ScaleMax;
	}

	void SetLifeTimeMin(float Min)
	{
		m_BufferData.LifeTimeMin = Min;
	}

	void SetLifeTimeMax(float Max)
	{
		m_BufferData.LifeTimeMax = Max;
	}

	void SetColorMin(const Vector4& ColorMin)
	{
		m_BufferData.ColorMin = ColorMin;
	}

	void SetColorMax(const Vector4& ColorMax)
	{
		m_BufferData.ColorMax = ColorMax;
	}

	void SetSpeedMin(float SpeedMin)
	{
		m_BufferData.SpeedMin = SpeedMin;
	}

	void SetSpeedMax(float SpeedMax)
	{
		m_BufferData.SpeedMax = SpeedMax;
	}

	void SetMove(bool Move)
	{
		m_BufferData.Move = Move ? 1 : 0;
	}

	void SetGravity(bool Gravity)
	{
		m_BufferData.Gravity = Gravity ? 1 : 0;
	}

	void SetMoveDir(const Vector3& MoveDir)
	{
		m_BufferData.MoveDir = MoveDir;
	}

	void Set2D(bool Is2D)
	{
		m_BufferData.Is2D = Is2D ? 1 : 0;
	}

	void SetMoveAngle(const Vector3& MoveAngle)
	{
		m_BufferData.MoveAngle = MoveAngle;
	}
};

