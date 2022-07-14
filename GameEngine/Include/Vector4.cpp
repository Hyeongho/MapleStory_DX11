#include "Vector4.h"
#include "Vector3.h"

Vector4 Vector4::Black(0.f, 0.f, 0.f, 1.f);
Vector4 Vector4::White(1.f, 1.f, 1.f, 1.f);
Vector4 Vector4::Red(1.f, 0.f, 0.f, 1.f);
Vector4 Vector4::Green(0.f, 1.f, 0.f, 1.f);
Vector4 Vector4::Blue(0.f, 0.f, 1.f, 1.f);

Vector4::Vector4() : x(0.f), y(0.f), z(0.f), w(0.f)
{
}

Vector4::Vector4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w)
{
}

Vector4::Vector4(const Vector4& v) : x(v.x), y(v.y), z(v.z), w(v.w)
{
}

Vector4::Vector4(const XMVECTOR& v)
{
	XMStoreFloat4((XMFLOAT4*)this, v);
}

Vector4& Vector4::operator=(const Vector4& v)
{
	x = v.x;
	y = v.y;
	z = v.z;
	w = v.w;

	return *this;
}

Vector4& Vector4::operator=(const XMVECTOR& v)
{
	XMStoreFloat4((XMFLOAT4*)this, v);

	return *this;
}

Vector4& Vector4::operator=(float f)
{
	x = f;
	y = f;
	z = f;
	w = f;

	return *this;
}

bool Vector4::operator==(const Vector4& v) const
{
	return x == v.x && y == v.y && z == v.z && w == v.w;
}

bool Vector4::operator==(const XMVECTOR& v) const
{
	Vector4	v1;
	XMStoreFloat4((XMFLOAT4*)&v1, v);

	return x == v1.x && y == v1.y && z == v1.z && w == v1.w;
}

bool Vector4::operator!=(const Vector4& v) const
{
	return x != v.x || y != v.y || z != v.z || w != v.w;
}

bool Vector4::operator!=(const XMVECTOR& v) const
{
	Vector4	v1;
	XMStoreFloat4((XMFLOAT4*)&v1, v);

	return x != v1.x || y != v1.y || z != v1.z || w != v1.w;
}

float& Vector4::operator[](int Index)
{
	if (Index < 0 || Index > 3)
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

	else if (2 == Index)
	{
		return z;
	}

	return w;
}

// +
Vector4 Vector4::operator+(const Vector4& v) const
{
	XMVECTOR v1 = Convert();
	XMVECTOR v2 = v.Convert();

	return Vector4(v1 + v2);
}

Vector4 Vector4::operator+(const XMVECTOR& v) const
{
	return Vector4(Convert() + v);
}

Vector4 Vector4::operator+(const float f) const
{
	return Vector4(x + f, y + f, z + f, w + f);
}

// +=
Vector4 Vector4::operator+=(const Vector4& v)
{
	XMVECTOR v1 = Convert();
	XMVECTOR v2 = v.Convert();

	Convert(v1 + v2);

	return *this;
}

Vector4 Vector4::operator+=(const XMVECTOR& v)
{
	XMVECTOR v1 = Convert();

	Convert(v1 + v);

	return *this;
}

Vector4 Vector4::operator+=(const float f)
{
	x += f;
	y += f;
	z += f;
	w += f;

	return *this;
}

// -
Vector4 Vector4::operator-(const Vector4& v) const
{
	XMVECTOR v1 = Convert();
	XMVECTOR v2 = v.Convert();

	return Vector4(v1 - v2);
}

Vector4 Vector4::operator-(const XMVECTOR& v) const
{
	return Vector4(Convert() - v);
}

Vector4 Vector4::operator-(const float f) const
{
	return Vector4(x - f, y - f, z - f, w - f);
}

// -=
Vector4 Vector4::operator-=(const Vector4& v)
{
	XMVECTOR v1 = Convert();
	XMVECTOR v2 = v.Convert();

	Convert(v1 - v2);

	return *this;
}

Vector4 Vector4::operator-=(const XMVECTOR& v)
{
	XMVECTOR v1 = Convert();

	Convert(v1 - v);

	return *this;
}

Vector4 Vector4::operator-=(const float f)
{
	x -= f;
	y -= f;
	z -= f;
	w -= f;

	return *this;
}

// *
Vector4 Vector4::operator*(const Vector4& v) const
{
	XMVECTOR v1 = Convert();
	XMVECTOR v2 = v.Convert();

	return Vector4(v1 * v2);
}

Vector4 Vector4::operator*(const XMVECTOR& v) const
{
	return Vector4(Convert() * v);
}

Vector4 Vector4::operator*(const float f) const
{
	return Vector4(x * f, y * f, z * f, w * f);
}

// *=
Vector4 Vector4::operator*=(const Vector4& v)
{
	XMVECTOR v1 = Convert();
	XMVECTOR v2 = v.Convert();

	Convert(v1 * v2);

	return *this;
}

Vector4 Vector4::operator*=(const XMVECTOR& v)
{
	XMVECTOR v1 = Convert();

	Convert(v1 * v);

	return *this;
}

Vector4 Vector4::operator*=(const float f)
{
	x *= f;
	y *= f;
	z *= f;
	w *= f;

	return *this;
}

// /
Vector4 Vector4::operator/(const Vector4& v) const
{
	XMVECTOR v1 = Convert();
	XMVECTOR v2 = v.Convert();

	return Vector4(v1 / v2);
}

Vector4 Vector4::operator/(const XMVECTOR& v) const
{
	return Vector4(Convert() / v);
}

Vector4 Vector4::operator/(const float f) const
{
	return Vector4(x / f, y / f, z / f, w / f);
}

// /=
Vector4 Vector4::operator/=(const Vector4& v)
{
	XMVECTOR v1 = Convert();
	XMVECTOR v2 = v.Convert();

	Convert(v1 / v2);

	return *this;
}

Vector4 Vector4::operator/=(const XMVECTOR& v)
{
	XMVECTOR v1 = Convert();

	Convert(v1 / v);

	return *this;
}

Vector4 Vector4::operator/=(const float f)
{
	x /= f;
	y /= f;
	z /= f;
	w /= f;

	return *this;
}

Vector4 Vector4::operator++()
{
	x += 1.f;
	y += 1.f;
	z += 1.f;
	w += 1.f;

	return *this;
}

Vector4 Vector4::operator++(int)
{
	x += 1.f;
	y += 1.f;
	z += 1.f;
	w += 1.f;

	return *this;
}

Vector4 Vector4::operator--()
{
	x -= 1.f;
	y -= 1.f;
	z -= 1.f;
	w -= 1.f;

	return *this;
}

Vector4 Vector4::operator--(int)
{
	x -= 1.f;
	y -= 1.f;
	z -= 1.f;
	w -= 1.f;

	return *this;
}

XMVECTOR Vector4::Convert()	const
{
	return XMLoadFloat4((XMFLOAT4*)this);
}

void Vector4::Convert(const XMVECTOR& v)
{
	XMStoreFloat4((XMFLOAT4*)this, v);
}
