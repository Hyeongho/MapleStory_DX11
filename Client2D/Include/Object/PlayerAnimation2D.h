#pragma once

#include "Animation/AnimationSequence2DInstance.h"

class CPlayerAnimation2D :
    public CAnimationSequence2DInstance
{
	friend class CPlayer2D;

public:
	CPlayerAnimation2D();
	CPlayerAnimation2D(const CPlayerAnimation2D& Anim);
	~CPlayerAnimation2D();

private:	
	class CPlayer2D* m_Player;

public:
	virtual bool Init();
	virtual CPlayerAnimation2D* Clone();

public:
	virtual void Update(float DeltaTime);
};

