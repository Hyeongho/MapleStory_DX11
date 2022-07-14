#include "Collision.h"
#include "../Component/ColliderBox2D.h"
#include "../Component/ColliderCircle.h"
#include "../Component/ColliderPixel.h"

bool CCollision::CollisionBox2DToBox2D(CColliderBox2D* Src, CColliderBox2D* Dest)
{
	CollisionResult	srcResult, destResult;

	if (CollisionBox2DToBox2D(srcResult, destResult, Src->GetInfo(), Dest->GetInfo()))
	{
		srcResult.Src = Src;
		srcResult.Dest = Dest;

		destResult.Src = Dest;
		destResult.Dest = Src;

		Src->m_Result = srcResult;
		Dest->m_Result = destResult;

		return true;
	}

	return false;
}

bool CCollision::CollisionCircleToCircle(CColliderCircle* Src, CColliderCircle* Dest)
{
	CollisionResult	srcResult, destResult;

	if (CollisionCircleToCircle(srcResult, destResult, Src->GetInfo(), Dest->GetInfo()))
	{
		srcResult.Src = Src;
		srcResult.Dest = Dest;

		destResult.Src = Dest;
		destResult.Dest = Src;

		Src->m_Result = srcResult;
		Dest->m_Result = destResult;

		return true;
	}

	return false;
}

bool CCollision::CollisionBox2DToCircle(CColliderBox2D* Src, CColliderCircle* Dest)
{
	CollisionResult	srcResult, destResult;

	if (CollisionBox2DToCircle(srcResult, destResult, Src->GetInfo(), Dest->GetInfo()))
	{
		srcResult.Src = Src;
		srcResult.Dest = Dest;

		destResult.Src = Dest;
		destResult.Dest = Src;

		Src->m_Result = srcResult;
		Dest->m_Result = destResult;

		return true;
	}

	return false;
}

bool CCollision::CollisionBox2DToPixel(CColliderBox2D* Src, CColliderPixel* Dest)
{
	CollisionResult	srcResult, destResult;

	if (CollisionBox2DToPixel(srcResult, destResult, Src->GetInfo(), Dest->GetInfo()))
	{
		srcResult.Src = Src;
		srcResult.Dest = Dest;

		destResult.Src = Dest;
		destResult.Dest = Src;

		Src->m_Result = srcResult;
		Dest->m_Result = destResult;

		return true;
	}

	return false;
}

bool CCollision::CollisionCircleToPixel(CColliderCircle* Src, CColliderPixel* Dest)
{
	CollisionResult	srcResult, destResult;

	if (CollisionCircleToPixel(srcResult, destResult, Src->GetInfo(), Dest->GetInfo()))
	{
		srcResult.Src = Src;
		srcResult.Dest = Dest;

		destResult.Src = Dest;
		destResult.Dest = Src;

		Src->m_Result = srcResult;
		Dest->m_Result = destResult;

		return true;
	}

	return false;
}

bool CCollision::CollisionBox2DToBox2D(CollisionResult& SrcResult, CollisionResult& DestResult, const Box2DInfo& Src, const Box2DInfo& Dest)
{
	Vector2	CenterDir = Src.Center - Dest.Center;

	Vector2	Axis = Src.Axis[0];

	float CenterProjDist = abs(CenterDir.Dot(Axis));

	float r1, r2;

	r1 = Src.Length.x;
	r2 = abs(Dest.Axis[0].Dot(Axis) * Dest.Length.x) + abs(Dest.Axis[1].Dot(Axis) * Dest.Length.y);

	if (CenterProjDist > r1 + r2)
	{
		return false;
	}

	Axis = Src.Axis[1];

	CenterProjDist = abs(CenterDir.Dot(Axis));

	r1 = Src.Length.y;
	r2 = abs(Dest.Axis[0].Dot(Axis) * Dest.Length.x) + abs(Dest.Axis[1].Dot(Axis) * Dest.Length.y);

	if (CenterProjDist > r1 + r2)
	{
		return false;
	}

	Axis = Dest.Axis[0];

	CenterProjDist = abs(CenterDir.Dot(Axis));

	r1 = Dest.Length.x;
	r2 = abs(Src.Axis[0].Dot(Axis) * Src.Length.x) + abs(Src.Axis[1].Dot(Axis) * Src.Length.y);

	if (CenterProjDist > r1 + r2)
	{
		return false;
	}

	Axis = Dest.Axis[1];

	CenterProjDist = abs(CenterDir.Dot(Axis));

	r1 = Dest.Length.y;
	r2 = abs(Src.Axis[0].Dot(Axis) * Src.Length.x) + abs(Src.Axis[1].Dot(Axis) * Src.Length.y);

	if (CenterProjDist > r1 + r2)
	{
		return false;
	}

	return true;
}

bool CCollision::CollisionCircleToCircle(CollisionResult& SrcResult, CollisionResult& DestResult, const CircleInfo& Src, const CircleInfo& Dest)
{
	float Dist = Src.Center.Distance(Dest.Center);

	return Dist <= Src.Radius + Dest.Radius;
}

bool CCollision::CollisionBox2DToCircle(CollisionResult& SrcResult, CollisionResult& DestResult, const Box2DInfo& Src, const CircleInfo& Dest)
{
	Vector2	CenterDir = Src.Center - Dest.Center;

	Vector2	Axis = Src.Axis[0];

	float CenterProjDist = abs(CenterDir.Dot(Axis));
		  
	float r1, r2;

	r1 = Src.Length.x;
	r2 = Dest.Radius;

	if (CenterProjDist > r1 + r2)
	{
		return false;
	}

	Axis = Src.Axis[1];

	CenterProjDist = abs(CenterDir.Dot(Axis));

	r1 = Src.Length.y;
	r2 = Dest.Radius;

	if (CenterProjDist > r1 + r2)
	{
		return false;
	}

	Axis = CenterDir;
	Axis.Normalize();

	CenterProjDist = CenterDir.Length();

	r1 = abs(Src.Axis[0].Dot(Axis) * Src.Length.x) + abs(Src.Axis[1].Dot(Axis) * Src.Length.y);
	r2 = Dest.Radius;

	if (CenterProjDist > r1 + r2)
	{
		return false;
	}

	return true;
}

bool CCollision::CollisionBox2DToPixel(CollisionResult& SrcResult, CollisionResult& DestResult, const Box2DInfo& Src, const PixelInfo& Dest)
{
	if (!CollisionBox2DToBox2D(SrcResult, DestResult, Src, Dest.Box))
	{
		return false;
	}

	// 교집합을 구한다.
	float Left = Src.Min.x < Dest.Min.x ? Dest.Min.x : Src.Min.x;
	float Right = Src.Max.x > Dest.Max.x ? Dest.Max.x : Src.Max.x;

	float Bottom = Src.Min.y < Dest.Min.y ? Dest.Min.y : Src.Min.y;
	float Top = Src.Max.y > Dest.Max.y ? Dest.Max.y : Src.Max.y;

	// 월드 공간에서의 좌 하단 좌표를 구한다.
	Vector2	LB = Dest.Box.Center - Dest.Box.Length;

	Left -= LB.x;
	Right -= LB.x;

	Bottom -= LB.y;
	Top -= LB.y;

	Left = Left < 0.f ? 0.f : Left;
	Bottom = Bottom < 0.f ? 0.f : Bottom;

	Right = Right >= (float)Dest.Width ? (float)Dest.Width - 1.f : Right;
	Top = Top >= (float)Dest.Height ? (float)Dest.Height - 1.f : Top;

	Top = Dest.Height - Top;
	Bottom = Dest.Height - Bottom;

	bool Collision = false;

	// 교집합 구간을 반복한다.
	for (int y = (int)Top; y < (int)Bottom; y++)
	{
		for (int x = (int)Left; x < (int)Right; x++)
		{
			int	Index = y * (int)Dest.Width * 4 + x * 4;

			// 현재 인덱스의 픽셀이 상대방 박스 안에 존재하는지를 판단한다.
			// 현재 픽셀의 월드공간에서의 위치를 구해준다.
			Vector2	PixelWorldPos = LB + Vector2((float)x, (float)Dest.Height - (float)y);
			if (!CollisionBox2DToPoint(SrcResult, DestResult, Src, PixelWorldPos))
			{
				continue;
			}

			switch (Dest.Type)
			{
			case PixelCollision_Type::Color_Ignore:
				if (Dest.Pixel[Index] == Dest.Color[0] && Dest.Pixel[Index + 1] == Dest.Color[1] && Dest.Pixel[Index + 2] == Dest.Color[2])
				{
					continue;
				}

				Collision = true;
				break;
			case PixelCollision_Type::Color_Confirm:
				if (Dest.Pixel[Index] == Dest.Color[0] && Dest.Pixel[Index + 1] == Dest.Color[1] && Dest.Pixel[Index + 2] == Dest.Color[2])
				{
					Collision = true;
				}
				break;
			case PixelCollision_Type::Alpha_Ignore:
				if (Dest.Pixel[Index + 3] == Dest.Color[3])
				{
					continue;
				}

				Collision = true;
				break;
			case PixelCollision_Type::Alpha_Confirm:
				if (Dest.Pixel[Index + 3] == Dest.Color[3])
				{
					Collision = true;
				}
				break;
			}

			if (Collision)
			{
				break;
			}
		}

		if (Collision)
		{
			break;
		}
	}

	return Collision;
}

bool CCollision::CollisionCircleToPixel(CollisionResult& SrcResult, CollisionResult& DestResult, const CircleInfo& Src, const PixelInfo& Dest)
{
	if (!CollisionBox2DToCircle(SrcResult, DestResult, Dest.Box, Src))
	{
		return false;
	}

	// 교집합을 구한다.
	float Left = Src.Min.x < Dest.Min.x ? Dest.Min.x : Src.Min.x;
	float Right = Src.Max.x > Dest.Max.x ? Dest.Max.x : Src.Max.x;

	float	Bottom = Src.Min.y < Dest.Min.y ? Dest.Min.y : Src.Min.y;
	float	Top = Src.Max.y > Dest.Max.y ? Dest.Max.y : Src.Max.y;

	// 월드 공간에서의 좌 하단 좌표를 구한다.
	Vector2	LB = Dest.Box.Center - Dest.Box.Length;

	Left -= LB.x;
	Right -= LB.x;

	Bottom -= LB.y;
	Top -= LB.y;

	Left = Left < 0.f ? 0.f : Left;
	Bottom = Bottom < 0.f ? 0.f : Bottom;

	Right = Right >= (float)Dest.Width ? (float)Dest.Width - 1.f : Right;
	Top = Top >= (float)Dest.Height ? (float)Dest.Height - 1.f : Top;

	Top = Dest.Height - Top;
	Bottom = Dest.Height - Bottom;

	bool Collision = false;

	// 교집합 구간을 반복한다.
	for (int y = (int)Top; y < (int)Bottom; y++)
	{
		for (int x = (int)Left; x < (int)Right; x++)
		{
			int	Index = y * (int)Dest.Width * 4 + x * 4;

			// 현재 인덱스의 픽셀이 상대방 박스 안에 존재하는지를 판단한다.
			// 현재 픽셀의 월드공간에서의 위치를 구해준다.
			Vector2	PixelWorldPos = LB + Vector2((float)x, (float)Dest.Height - (float)y);
			if (!CollisionCircleToPoint(SrcResult, DestResult, Src, PixelWorldPos))
			{
				continue;
			}

			switch (Dest.Type)
			{
			case PixelCollision_Type::Color_Ignore:
				if (Dest.Pixel[Index] == Dest.Color[0] && Dest.Pixel[Index + 1] == Dest.Color[1] && Dest.Pixel[Index + 2] == Dest.Color[2])
				{
					continue;
				}

				Collision = true;
				break;
			case PixelCollision_Type::Color_Confirm:
				if (Dest.Pixel[Index] == Dest.Color[0] && Dest.Pixel[Index + 1] == Dest.Color[1] && Dest.Pixel[Index + 2] == Dest.Color[2])
				{
					Collision = true;
				}
				break;
			case PixelCollision_Type::Alpha_Ignore:
				if (Dest.Pixel[Index + 3] == Dest.Color[3])
				{
					continue;
				}

				Collision = true;
				break;
			case PixelCollision_Type::Alpha_Confirm:
				if (Dest.Pixel[Index + 3] == Dest.Color[3])
				{
					Collision = true;
				}
				break;
			}

			if (Collision)
			{
				break;
			}
		}

		if (Collision)
		{
			break;
		}
	}

	return Collision;
}

bool CCollision::CollisionBox2DToPoint(CollisionResult& SrcResult, CollisionResult& DestResult, const Box2DInfo& BoxInfo, const Vector2& Point)
{
	// 상자의 x, y 축에 점을 투영하여 구간이 겹치는지 판단한다.
	Vector2	CenterDir = BoxInfo.Center - Point;

	Vector2	Axis = BoxInfo.Axis[0];

	float	CenterProjDist = abs(CenterDir.Dot(Axis));

	if (CenterProjDist > BoxInfo.Length.x)
	{
		return false;
	}

	Axis = BoxInfo.Axis[1];

	CenterProjDist = abs(CenterDir.Dot(Axis));

	if (CenterProjDist > BoxInfo.Length.y)
	{	
		return false;
	}

	return true;
}

bool CCollision::CollisionCircleToPoint(CollisionResult& SrcResult, CollisionResult& DestResult, const CircleInfo& CircleInfo, const Vector2& Point)
{
	float Dist = CircleInfo.Center.Distance(Point);

	return CircleInfo.Radius >= Dist;
}

bool CCollision::CollisionPixelToPoint(CollisionResult& SrcResult, CollisionResult& DestResult, const PixelInfo& PixelInfo, const Vector2& Point)
{
	if (!CollisionBox2DToPoint(SrcResult, DestResult, PixelInfo.Box, Point))
	{
		return false;
	}

	Vector2	LB = PixelInfo.Box.Center - PixelInfo.Box.Length;

	Vector2	ConvertPoint = Point - LB;

	ConvertPoint.y = PixelInfo.Height - ConvertPoint.y;

	int	Index = (int)ConvertPoint.y * (int)PixelInfo.Width * 4 + (int)ConvertPoint.x * 4;

	bool Result = false;

	switch (PixelInfo.Type)
	{
	case PixelCollision_Type::Color_Ignore:
		if (PixelInfo.Pixel[Index] == PixelInfo.Color[0] && PixelInfo.Pixel[Index + 1] == PixelInfo.Color[1] && PixelInfo.Pixel[Index + 2] == PixelInfo.Color[2])
		{
			Result = false;
		}

		else
		{
			Result = true;
		}
		break;
	case PixelCollision_Type::Color_Confirm:
		if (PixelInfo.Pixel[Index] == PixelInfo.Color[0] && PixelInfo.Pixel[Index + 1] == PixelInfo.Color[1] && PixelInfo.Pixel[Index + 2] == PixelInfo.Color[2])
		{
			Result = true;
		}

		else
		{
			Result = false;
		}
		break;
	case PixelCollision_Type::Alpha_Ignore:
		if (PixelInfo.Pixel[Index + 3] == PixelInfo.Color[3])
		{
			Result = false;
		}

		else
		{
			Result = true;
		}
		break;
	case PixelCollision_Type::Alpha_Confirm:
		if (PixelInfo.Pixel[Index + 3] == PixelInfo.Color[3])
		{
			Result = true;
		}

		else
		{
			Result = false;
		}
		break;
	}

	return Result;
}
