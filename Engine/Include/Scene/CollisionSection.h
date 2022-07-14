#pragma once

#include "../GameInfo.h"

class CCollisionSection
{
	friend class CSceneCollision;

private:
	CCollisionSection();
	~CCollisionSection();

private:
	std::vector<class CColliderComponent*> m_vecCollider;
	Vector3 m_SectionSize;
	Vector3 m_SectionTotalSize;
	Vector3 m_Min;
	Vector3 m_Max;
	int m_IndexX;
	int m_IndexY;
	int m_IndexZ;
	int m_Index;

public:
	void Init(int IndexX, int IndexY, int IndexZ, int Index, const Vector3& Min, const Vector3& Max, const Vector3& SectionSize, const Vector3& SectionTotalSize);
	void Clear();
	void AddCollider(class CColliderComponent* Collider);
	void Collision(float DeltaTime);
	class CColliderComponent* CollisionMouse(bool Is2D, float DeltaTime);

private:
	static int SortY(const void* Src, const void* Dest);
};

