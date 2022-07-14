#pragma once

#include "../GameInfo.h"

class CCollision
{
public:
	static bool CollisionBox2DToBox2D(class CColliderBox2D* Src, class CColliderBox2D* Dest);
	static bool CollisionCircleToCircle(class CColliderCircle* Src, class CColliderCircle* Dest);
	static bool CollisionBox2DToCircle(class CColliderBox2D* Src, class CColliderCircle* Dest);
	static bool CollisionBox2DToPixel(class CColliderBox2D* Src, class CColliderPixel* Dest);
	static bool CollisionCircleToPixel(class CColliderCircle* Src, class CColliderPixel* Dest);

public:
	static bool CollisionBox2DToBox2D(CollisionResult& SrcResult, CollisionResult& DestResult, const Box2DInfo& Src, const Box2DInfo& Dest);
	static bool CollisionCircleToCircle(CollisionResult& SrcResult, CollisionResult& DestResult, const CircleInfo& Src, const CircleInfo& Dest);
	static bool CollisionBox2DToCircle(CollisionResult& SrcResult, CollisionResult& DestResult, const Box2DInfo& Src, const CircleInfo& Dest);
	static bool CollisionBox2DToPixel(CollisionResult& SrcResult, CollisionResult& DestResult, const Box2DInfo& Src, const PixelInfo& Dest);
	static bool CollisionCircleToPixel(CollisionResult& SrcResult, CollisionResult& DestResult, const CircleInfo& Src, const PixelInfo& Dest);

	static bool CollisionBox2DToPoint(CollisionResult& SrcResult, CollisionResult& DestResult, const Box2DInfo& BoxInfo, const Vector2& Point);
	static bool CollisionCircleToPoint(CollisionResult& SrcResult, CollisionResult& DestResult, const CircleInfo& CircleInfo, const Vector2& Point);
	static bool CollisionPixelToPoint(CollisionResult& SrcResult, CollisionResult& DestResult, const PixelInfo& PixelInfo, const Vector2& Point);
};

