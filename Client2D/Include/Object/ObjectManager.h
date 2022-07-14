#pragma once

#include "GameObject/GameObject.h"
#include "../ClientInfo.h"

class CObjectManager :
    public CGameObject
{
	friend class CScene;

public:
	CObjectManager();
	CObjectManager(const CObjectManager& obj);
	virtual ~CObjectManager();

protected:
	CharacterInfo m_CharacterInfo;

protected:
	float m_MoveSpeed;
	float m_TimeScale;
	float m_LifeTime;

	bool m_CameraCull;

	bool m_PhysicsSimulate;
	float m_GravityAccel;
	bool m_IsGround;
	float m_FallTime;
	float m_FallStartY;
	float m_FallStartX;
	bool m_Jump;
	float m_JumpVelocity;
	bool m_SideWallCheck;
	bool m_FloorCheck;
	float m_Dir;

	Vector3 m_Range;
	Vector3 m_StartRange;
	Vector3 m_EndRange;

public:
	void SetCharacterInfo(int Attack, int Armor, int HP, int MP, int Level, int Exp, int Gold, float AttackSpeed, float AttackDistance)
	{
		m_CharacterInfo.Attack = Attack;
		m_CharacterInfo.Armor = Armor;
		m_CharacterInfo.HP = HP;
		m_CharacterInfo.MaxHP = HP;
		m_CharacterInfo.MP = MP;
		m_CharacterInfo.MaxMP = MP;
		m_CharacterInfo.Level = Level;
		m_CharacterInfo.Exp = Exp;
	}

	void SetCharacterInfo(int Attack, int Armor, int HP, int MP, int Level, int Exp)
	{
		m_CharacterInfo.Attack = Attack;
		m_CharacterInfo.Armor = Armor;
		m_CharacterInfo.HP = HP;
		m_CharacterInfo.MaxHP = HP;
		m_CharacterInfo.MP = MP;
		m_CharacterInfo.MaxMP = MP;
		m_CharacterInfo.Level = Level;
		m_CharacterInfo.Exp = Exp;
	}

	void SetCharacterInfo(CharacterInfo CharacterInfo)
	{
		m_CharacterInfo = CharacterInfo;
	}

	CharacterInfo GetCharacterInfo() const
	{
		return m_CharacterInfo;
	}

public:
	void SetSideWallCheck(bool Check)
	{
		m_SideWallCheck = Check;
	}

	void SetFloorCheck(bool Check)
	{
		m_FloorCheck = Check;
	}

	void SetGravityAccel(float Accel)
	{
		m_GravityAccel = Accel;
	}

	void SetPhysicsSimulate(bool Physics)
	{
		m_PhysicsSimulate = Physics;
	}

	void SetJumpVelocity(float JumpVelocity)
	{
		m_JumpVelocity = JumpVelocity;
	}

	void SetRange(float x, float y, float z)
	{
		m_Range.x = x;
		m_Range.y = y;
		m_Range.z = z;
	}

	void SetRange(float StartX, float StartY, float StartZ, float EndX, float EndY, float EndZ)
	{
		m_StartRange.x = StartX;
		m_StartRange.y = StartY;
		m_StartRange.z = StartZ;

		m_EndRange.x = EndX;
		m_EndRange.y = EndY;
		m_EndRange.z = EndZ;
	}

	void SetRange(const Vector3& Range)
	{
		m_Range = Range;
	}

	void SetRange(const Vector3& StartRange, const Vector3& EndRange)
	{
		m_StartRange = StartRange;
		m_EndRange = EndRange;
	}

	void Jump(bool Direction)
	{
		if (!m_Jump)
		{
			Vector3 Pos = GetWorldPos();

			m_Jump = true;
			m_IsGround = false;

			m_FallTime = 0.f;
			m_FallStartY = Pos.y;

			if (Direction)
			{
				m_Dir = 1.0f;
			}

			else
			{
				m_Dir = -1.0f;
			}
		}
	}

	bool IsCull() const
	{
		return m_CameraCull;
	}

public:
	Vector3 GetRange() const
	{
		return m_Range;
	}

public:
	virtual void Start();
	virtual bool Init();
	virtual void Update(float DeltaTime);
	virtual void PostUpdate(float DeltaTime);
	virtual CObjectManager* Clone();
	virtual float SetDamage(float Damage);

protected:
	void SetCharacterInfo(const std::string& name);
};

