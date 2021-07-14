#include "Vector2.h"
#include <math.h>

#include "DebugNew.h"

Vector2 Vector2::operator+(Vector2 _lhs)
{
	Vector2 result;

	result.x = x + _lhs.x;
	result.y = y + _lhs.y;

	return result;
}

Vector2 Vector2::operator-(Vector2 _lhs)
{
	Vector2 result;

	result.x = x - _lhs.x;
	result.y = y - _lhs.y;

	return result;
}


Vector2 Vector2::Add(Vector2 _lhs, Vector2 _rhs)
{
	Vector2 result;

	result.x = _lhs.x + _rhs.x;
	result.y = _lhs.y + _rhs.y;

	return result;
}

Vector2 Vector2::Subtract(Vector2 _lhs, Vector2 _rhs)
{
	Vector2 result;

	result.x = _lhs.x - _rhs.x;
	result.y = _lhs.y - _rhs.y;

	return result;
}

float Vector2::Magnitude()
{
	return (float)sqrt((x * x) + (y * y));
}

Vector2 Vector2::Normalize()
{
	Vector2 result;
	// Divide elements by their magnitude
	float magnitude = Magnitude();
	if (magnitude != 0)
	{
		result.x = x /= magnitude;
		result.y = y /= magnitude;
		return result;
	}

}

void Vector2::Multiply(float _float)
{
	x *= _float;
	y *= _float;
}

Vector2 Vector2::Scale(float _scaleFactor)
{
	Vector2 result;

	result.x = x * _scaleFactor;
	result.y = y *_scaleFactor;

	return result;
}
