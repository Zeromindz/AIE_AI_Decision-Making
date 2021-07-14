#pragma once
#include "Object.h"
class DynamicObject : public Object
{
public:
	DynamicObject() {}
	~DynamicObject() {}

	virtual void Update(float _deltaTime);
	virtual void Draw(aie::Renderer2D* _renderer);

	// Movement functions
	Vector2 GetVelocity() { return m_Velocity; }
	void SetVelocity(Vector2 _velocity) { m_Velocity = _velocity; }
	Vector2 GetForce() { return m_Force; }
	void AddForce(Vector2 _force) { m_Force = m_Force + _force; }

	float GetMaxSpeed() { return m_MaxSpeed; }
	void SetMaxSpeed(float _maxSpeed) { m_MaxSpeed = _maxSpeed; }
	float GetFriction() { return m_FrictionModifier; }
	void SetFriction(float _friction) { m_FrictionModifier = _friction; }

private:
	Vector2 m_Velocity = { 0, 0 };
	Vector2 m_Force = { 0, 0 };

	float m_FrictionModifier = 0.99f;
	float m_MaxSpeed = 200;
};

