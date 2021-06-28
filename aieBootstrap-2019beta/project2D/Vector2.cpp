#include "Vector2.h"

Vector2 Vector2::operator+(Vector2 _param)
{
	Vector2 result;

	result.x = x + _param.x;
	result.y = y + _param.y;

	return result;
}

Vector2 Vector2::operator-(Vector2 _param)
{
	Vector2 result;

	result.x = x - _param.x;
	result.y = y - _param.y;

	return result;
}

Vector2 Vector2::operator*(Vector2 _param)
{
	Vector2 result;

	result.x = x * _param.x;
	result.y = y * _param.y;

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

Vector2 Vector2::Scale(float _scaleFactor)
{
	Vector2 result;

	result.x = x * _scaleFactor;
	result.y = y *_scaleFactor;

	return result;
}
