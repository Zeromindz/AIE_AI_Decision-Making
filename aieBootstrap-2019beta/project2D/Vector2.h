#pragma once

struct Vector2
{
public:
	Vector2 operator+(Vector2);

	static Vector2 Add(Vector2 _lhs, Vector2 _rhs);
	Vector2 Scale(float _scaleFactor);

	float x;
	float y;
};