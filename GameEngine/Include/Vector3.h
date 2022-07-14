#pragma once

#include "EngineMath.h"
#include "Matrix.h"

struct Vector3
{
	float	x, y, z;

	Vector3();
	Vector3(float _x, float _y, float _z);
	Vector3(const Vector3& v);
	Vector3(const XMVECTOR& v);

	// operator =
	Vector3& operator = (const Vector3& v);
	Vector3& operator = (const XMVECTOR& v);
	Vector3& operator = (float f);

	// operator ==, !=
	bool operator == (const Vector3& v)	const;
	bool operator == (const XMVECTOR& v) const;
	bool operator != (const Vector3& v)	const;
	bool operator != (const XMVECTOR& v) const;

	float& operator [] (int Index);

	// operator +
	Vector3 operator + (const Vector3& v) const;
	Vector3 operator + (const XMVECTOR& v) const;
	Vector3 operator + (const float f) const;

	// operator +=
	void operator += (const Vector3& v);
	void operator += (const XMVECTOR& v);
	void operator += (const float f);

	// operator -
	Vector3 operator - (const Vector3& v) const;
	Vector3 operator - (const XMVECTOR& v) const;
	Vector3 operator - (const float f) const;

	// operator -=
	void operator -= (const Vector3& v);
	void operator -= (const XMVECTOR& v);
	void operator -= (const float f);

	// operator *
	Vector3 operator * (const Vector3& v) const;
	Vector3 operator * (const XMVECTOR& v) const;
	Vector3 operator * (const float f) const;

	// operator *=
	void operator *= (const Vector3& v);
	void operator *= (const XMVECTOR& v);
	void operator *= (const float f);

	// operator /
	Vector3 operator / (const Vector3& v) const;
	Vector3 operator / (const XMVECTOR& v) const;
	Vector3 operator / (const float f) const;

	// operator /=
	void operator /= (const Vector3& v);
	void operator /= (const XMVECTOR& v);
	void operator /= (const float f);

	// operator ++
	const Vector3& operator ++ ();
	const Vector3& operator ++ (int);

	// operator --
	const Vector3& operator -- ();
	const Vector3& operator -- (int);

	float Length()	const;
	float Distance(const Vector3& v) const;
	void Normalize();
	float Dot(const Vector3& v)	const;
	Vector3 Cross(const Vector3& v) const;
	float Angle(const Vector3& v) const;
	Vector3 ConvertAngle() const;

	// w = 0
	Vector3 TransformNormal(const Matrix& m) const;

	// w = 1
	Vector3 TransformCoord(const Matrix& m) const;

	XMVECTOR Convert()	const;
	void Convert(const XMVECTOR& v);

	static Vector3 Normalize(const Vector3& v);

	static Vector3	Zero;
	static Vector3	One;
	static Vector3	Axis[AXIS_MAX];
};

