#include <cmath>
#include "Vector2.h"
#include "Vector2F.h"

Vector2F Vector2F::vectorUp = { 0.0f,-1.0f };
Vector2F Vector2F::vectorDown = { 0.0f,1.0f };
Vector2F Vector2F::vectorLeft = { -1.0f,0.0f };
Vector2F Vector2F::vectorRight = { 1.0f,0.0f };

Vector2F::Vector2F()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2F::Vector2F(float vX, float vY)
{
	x = vX;
	y = vY;
}

Vector2F::Vector2F(Vector2 value)
{
	x = static_cast<float>(value.x);
	y = static_cast<float>(value.y);
}

Vector2F Vector2F::operator+(const Vector2F& value) const
{
	return { x + value.x, y + value.y };
}

Vector2F Vector2F::operator+=(const Vector2F& value)
{
	x += value.x;
	y += value.y;
	return *this;
}

Vector2F Vector2F::operator-(const Vector2F& value) const
{
	return { x - value.x, y - value.y };
}

Vector2F Vector2F::operator-=(const Vector2F& value)
{
	x -= value.x;
	y -= value.y;
	return *this;
}

Vector2F Vector2F::operator*(const float value) const
{
	return { x * value, y * value };
}

Vector2F Vector2F::operator/(const float value) const
{
	return { x / value, y / value };
}

float Vector2F::Magnitude()const
{
	return hypot(x, y);
}

void Vector2F::Normalize()
{
	float mag = Magnitude();
	x /= mag;
	y /= mag;
}