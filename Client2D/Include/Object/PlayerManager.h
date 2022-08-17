#pragma once

#include "GameObject/GameObject.h"
#include "GameInfo.h"
#include "../ClientInfo.h"
#include "Player2D.h"

class CPlayerManager :
	public CGameObject
{
	friend class CScene;
	friend class CViewport;

public:
	bool Init();

private:
	Gender m_Gender;
	bool m_TagPotal;
	std::string m_CurrentScene;

	EPlayer_State m_PlayerState;
	Player_Attack m_PlayerAttack;

public:
	void SetTagPotal(bool Tag)
	{
		m_TagPotal = Tag;
	}

	bool GetTagPotal() const
	{
		return m_TagPotal;
	}

	void SetGender(Gender gender)
	{
		m_Gender = gender;
	}

	Gender GetGender() const
	{
		return m_Gender;
	}

	void SetCurrentScene(std::string CurrentScene)
	{
		m_CurrentScene = CurrentScene;
	}

	std::string GetCurrnetScene() const
	{
		return m_CurrentScene;
	}

	void SetPlayerAttack(Player_Attack PlayerAttack)
	{
		m_PlayerAttack = PlayerAttack;
	}

	Player_Attack GetPlayerAttack()
	{
		return m_PlayerAttack;
	}

public:
	void SceneChange();

public:
	void PostUpdate(float DeltaTime);

	DECLARE_SINGLE(CPlayerManager)
};

