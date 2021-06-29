#pragma once

struct Vector2
{
public:
	Vector2 operator+(Vector2 _lhs);
	Vector2 operator-(Vector2 _lhs);
	static Vector2 Add(Vector2 _lhs, Vector2 _rhs);
	static Vector2 Subtract(Vector2 _lhs, Vector2 _rhs);
	float Magnitude();
	Vector2 Normalize();

	void Multiply(float _value);

	Vector2 Scale(float _scaleFactor);

	float x;
	float y;
};