#include "CollisionManager.h"

DEFINITION_SINGLE(CCollisionManager)

CCollisionManager::CCollisionManager()
{
}

CCollisionManager::~CCollisionManager()
{
	auto iter = m_mapProfile.begin();
	auto iterEnd = m_mapProfile.end();

	for (; iter != iterEnd; iter++)
	{
		SAFE_DELETE(iter->second);
	}
}

bool CCollisionManager::Init()
{
	CreateProfile("Object", Collision_Channel::Object, true);
	CreateProfile("Player", Collision_Channel::Player, true);
	CreateProfile("Monster", Collision_Channel::Monster, true);
	CreateProfile("PlayerAttack", Collision_Channel::PlayerAttack, true);
	CreateProfile("MonsterAttack", Collision_Channel::MonsterAttack, true);
	CreateProfile("Floor", Collision_Channel::Floor, true);
	CreateProfile("Potal", Collision_Channel::Potal, true);
	CreateProfile("PlayerBottom", Collision_Channel::PlayerBottom, true);

	SetCollisionState("Player", Collision_Channel::Player, Collision_Interaction::Ignore);
	SetCollisionState("Player", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	SetCollisionState("Player", Collision_Channel::PlayerBottom, Collision_Interaction::Ignore);

	SetCollisionState("Monster", Collision_Channel::Monster, Collision_Interaction::Ignore);
	SetCollisionState("Monster", Collision_Channel::MonsterAttack, Collision_Interaction::Ignore);
	SetCollisionState("Monster", Collision_Channel::PlayerBottom, Collision_Interaction::Ignore);

	SetCollisionState("PlayerAttack", Collision_Channel::Player, Collision_Interaction::Ignore);
	SetCollisionState("PlayerAttack", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	SetCollisionState("PlayerAttack", Collision_Channel::MonsterAttack, Collision_Interaction::Ignore);
	SetCollisionState("PlayerAttack", Collision_Channel::Floor, Collision_Interaction::Ignore);
	SetCollisionState("PlayerAttack", Collision_Channel::Potal, Collision_Interaction::Ignore);
	SetCollisionState("PlayerAttack", Collision_Channel::PlayerBottom, Collision_Interaction::Ignore);

	SetCollisionState("MonsterAttack", Collision_Channel::Monster, Collision_Interaction::Ignore);
	SetCollisionState("MonsterAttack", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	SetCollisionState("MonsterAttack", Collision_Channel::MonsterAttack, Collision_Interaction::Ignore);
	SetCollisionState("MonsterAttack", Collision_Channel::Floor, Collision_Interaction::Ignore);
	SetCollisionState("MonsterAttack", Collision_Channel::Potal, Collision_Interaction::Ignore);
	SetCollisionState("MonsterAttack", Collision_Channel::PlayerBottom, Collision_Interaction::Ignore);

	SetCollisionState("Potal", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	SetCollisionState("Potal", Collision_Channel::Monster, Collision_Interaction::Ignore);
	SetCollisionState("Potal", Collision_Channel::MonsterAttack, Collision_Interaction::Ignore);
	SetCollisionState("Potal", Collision_Channel::Floor, Collision_Interaction::Ignore);
	SetCollisionState("Potal", Collision_Channel::PlayerBottom, Collision_Interaction::Ignore);

	SetCollisionState("Floor", Collision_Channel::PlayerAttack, Collision_Interaction::Ignore);
	SetCollisionState("Floor", Collision_Channel::Potal, Collision_Interaction::Ignore);
	SetCollisionState("Floor", Collision_Channel::MonsterAttack, Collision_Interaction::Ignore);
	SetCollisionState("Floor", Collision_Channel::Monster, Collision_Interaction::Ignore);
	SetCollisionState("Floor", Collision_Channel::Player, Collision_Interaction::Ignore);

	return true;
}

bool CCollisionManager::CreateProfile(const std::string& Name, Collision_Channel Channel, bool Enable, Collision_Interaction State)
{
	CollisionProfile* Profile = FindProfile(Name);

	if (Profile)
	{
		return false;
	}

	Profile = new CollisionProfile;

	Profile->Name = Name;
	Profile->Channel = Channel;
	Profile->CollisionEnable = Enable;
	Profile->vecInteraction.resize((int)Collision_Channel::Max);

	for (int i = 0; i < (int)Collision_Channel::Max; ++i)
	{
		Profile->vecInteraction[i] = State;
	}

	m_mapProfile.insert(std::make_pair(Name, Profile));

	return true;
}

bool CCollisionManager::SetCollisionState(const std::string& Name, Collision_Channel Channel, Collision_Interaction State)
{
	CollisionProfile* Profile = FindProfile(Name);

	if (!Profile)
	{
		return false;
	}

	Profile->vecInteraction[(int)Channel] = State;

	return true;
}

CollisionProfile* CCollisionManager::FindProfile(const std::string& Name)
{
	auto iter = m_mapProfile.find(Name);

	if (iter == m_mapProfile.end())
	{
		return nullptr;
	}

	return iter->second;
}
