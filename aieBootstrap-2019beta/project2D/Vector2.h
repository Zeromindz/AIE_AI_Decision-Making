#pragma once

struct Vector2
{
public:
	Vector2 operator+(Vector2 _param);
	Vector2 operator-(Vector2 _param);
	Vector2 operator*(Vector2 _param);
	static Vector2 Add(Vector2 _lhs, Vector2 _rhs);
	static Vector2 Subtract(Vector2 _lhs, Vector2 _rhs);
	//static Vector2 Multiply(Vector2 _lhs, Vector2 _rhs);
	Vector2 Scale(float _scaleFactor);

	float x;
	float y;
};