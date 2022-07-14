#include "Vector3.h"

Vector3 Vector3::Zero;
Vector3 Vector3::One(1.f, 1.f, 1.f);
Vector3 Vector3::Axis[AXIS_MAX] =
{
	Vector3(1.f, 0.f, 0.f),
	Vector3(0.f, 1.f, 0.f),
	Vector3(0.f, 0.f, 1.f)
};

Vector3::Vector3() : x(0.f), y(0.f), z(0.f)
{
}

Vector3::Vector3(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
{
}

Vector3::Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z)
{
}

Vector3::Vector3(const XMVECTOR& v)
{
	XMStoreFloat3((XMFLOAT3*)this, v);
}

Vector3& Vector3::operator=(const Vector3& v)
{
	x = v.x;
	y = v.y;
	z = v.z;

	return *this;
}

Vector3& Vector3::operator=(const XMVECTOR& v)
{
	XMStoreFloat3((XMFLOAT3*)this, v);

	return *this;
}

Vector3& Vector3::operator=(float f)
{
	x = f;
	y = f;
	z = f;

	return *this;
}

bool Vector3::operator==(const Vector3& v) const
{
	return x == v.x && y == v.y && z == v.z;
}

bool Vector3::operator==(const XMVECTOR& v) const
{
	Vector3	v1;
	XMStoreFloat3((XMFLOAT3*)&v1, v);

	return x == v1.x && y == v1.y && z == v1.z;
}

bool Vector3::operator!=(const Vector3& v) const
{
	return x != v.x || y != v.y || z != v.z;
}

bool Vector3::operator!=(const XMVECTOR& v) const
{
	Vector3	v1;
	XMStoreFloat3((XMFLOAT3*)&v1, v);

	return x != v1.x || y != v1.y || z != v1.z;
}

float& Vector3::operator[](int Index)
{
	if (Index < 0 || Index > 2)
	{
		assert(false);
	}

	if (Index == 0)
	{
		return x;
	}

	else if (Index == 1)
	{
		return y;
	}

	return z;
}

// +
Vector3 Vector3::operator+(const Vector3& v) const
{
	XMVECTOR v1 = Convert();
	XMVECTOR v2 = v.Convert();

	return Vector3(v1 + v2);
}

Vector3 Vector3::operator+(const XMVECTOR& v) const
{
	return Vector3(Convert() + v);
}

Vector3 Vector3::operator+(const float f) const
{
	return Vector3(x + f, y + f, z + f);
}

// +=
void Vector3::operator+=(const Vector3& v)
{
	XMVECTOR v1 = Convert();
	XMVECTOR v2 = v.Convert();

	Convert(v1 + v2);
}

void Vector3::operator+=(const XMVECTOR& v)
{
	XMVECTOR	v1 = Convert();

	Convert(v1 + v);
}

void Vector3::operator+=(const float f)
{
	x += f;
	y += f;
	z += f;
}

// -
Vector3 Vector3::operator-(const Vector3& v) const
{
	XMVECTOR v1 = Convert();
	XMVECTOR v2 = v.Convert();

	return Vector3(v1 - v2);
}

Vector3 Vector3::operator-(const XMVECTOR& v) const
{
	return Vector3(Convert() - v);
}

Vector3 Vector3::operator-(const float f) const
{
	return Vector3(x - f, y - f, z - f);
}

// -=
void Vector3::operator-=(const Vector3& v)
{
	XMVECTOR v1 = Convert();
	XMVECTOR v2 = v.Convert();

	Convert(v1 - v2);
}

void Vector3::operator-=(const XMVECTOR& v)
{
	XMVECTOR v1 = Convert();

	Convert(v1 - v);
}

void Vector3::operator-=(const float f)
{
	x -= f;
	y -= f;
	z -= f;
}

// *
Vector3 Vector3::operator*(const Vector3& v) const
{
	XMVECTOR v1 = Convert();
	XMVECTOR v2 = v.Convert();

	return Vector3(v1 * v2);
}

Vector3 Vector3::operator*(const XMVECTOR& v) const
{
	return Vector3(Convert() * v);
}

Vector3 Vector3::operator*(const float f) const
{
	return Vector3(x * f, y * f, z * f);
}

// *=
void Vector3::operator*=(const Vector3& v)
{
	XMVECTOR v1 = Convert();
	XMVECTOR v2 = v.Convert();

	Convert(v1 * v2);
}

void Vector3::operator*=(const XMVECTOR& v)
{
	XMVECTOR v1 = Convert();

	Convert(v1 * v);
}

void Vector3::operator*=(const float f)
{
	x *= f;
	y *= f;
	z *= f;
}

// /
Vector3 Vector3::operator/(const Vector3& v) const
{
	XMVECTOR v1 = Convert();
	XMVECTOR v2 = v.Convert();

	return Vector3(v1 / v2);
}

Vector3 Vector3::operator/(const XMVECTOR& v) const
{
	return Vector3(Convert() / v);
}

Vector3 Vector3::operator/(const float f) const
{
	return Vector3(x / f, y / f, z / f);
}

// /=
void Vector3::operator/=(const Vector3& v)
{
	XMVECTOR v1 = Convert();
	XMVECTOR v2 = v.Convert();

	Convert(v1 / v2);
}

void Vector3::operator/=(const XMVECTOR& v)
{
	XMVECTOR v1 = Convert();

	Convert(v1 / v);
}

void Vector3::operator/=(const float f)
{
	x /= f;
	y /= f;
	z /= f;
}

const Vector3& Vector3::operator++()
{
	x += 1.f;
	y += 1.f;
	z += 1.f;

	return *this;
}

const Vector3& Vector3::operator++(int)
{
	x += 1.f;
	y += 1.f;
	z += 1.f;

	return *this;
}

const Vector3& Vector3::operator--()
{
	x -= 1.f;
	y -= 1.f;
	z -= 1.f;

	return *this;
}

const Vector3& Vector3::operator--(int)
{
	x -= 1.f;
	y -= 1.f;
	z -= 1.f;

	return *this;
}

float Vector3::Length() const
{
	return XMVectorGetX(XMVector3Length(Convert()));
}

float Vector3::Distance(const Vector3& v) const
{
	Vector3	Dist = v - *this;

	return Dist.Length();
}

void Vector3::Normalize()
{
	*this = XMVector3Normalize(Convert());
}

float Vector3::Dot(const Vector3& v) const
{
	return XMVectorGetX(XMVector3Dot(Convert(), v.Convert()));
}

Vector3 Vector3::Cross(const Vector3& v) const
{
	return XMVector3Cross(Convert(), v.Convert());
}

float Vector3::Angle(const Vector3& v) const
{
	Vector3	v1 = *this;
	Vector3	v2 = v;

	v1.Normalize();
	v2.Normalize();

	float	Angle = v1.Dot(v2);

	Angle = RadianToDegree(acosf(Angle));

	return Angle;
}

Vector3 Vector3::ConvertAngle()	const
{
	return Vector3(DegreeToRadian(x), DegreeToRadian(y), DegreeToRadian(z));
}

Vector3 Vector3::TransformNormal(const Matrix& m) const
{
	return Vector3(XMVector3TransformNormal(Convert(), m.m));
}


Vector3 Vector3::TransformCoord(const Matrix& m) const
{
	return Vector3(XMVector3TransformCoord(Convert(), m.m));
}

XMVECTOR Vector3::Convert()	const
{
	return XMLoadFloat3((XMFLOAT3*)this);
}

void Vector3::Convert(const XMVECTOR& v)
{
	XMStoreFloat3((XMFLOAT3*)this, v);
}

Vector3 Vector3::Normalize(const Vector3& v)
{
	return XMVector3Normalize(v.Convert());
}
