#pragma once
#include <Vector>
#include "Vector2.h"
#include "Renderer2D.h"

class IBehaviour;

struct MovementInfo
{
	Vector2 m_Position = { 0, 0 };
	Vector2 m_Velocity = { 0, 0 };
	Vector2 m_Force = { 0, 0 };
	float m_FrictionModifier = 0.99f;
	float m_MaxSpeed = 200;
};

class Agent
{
public:
	Agent();
	Agent(float _posX, float _posY);
	virtual ~Agent();

	// Update the agent and it's behaviour
	virtual void Update(float _deltaTime);

	// Draw the agent
	virtual void Draw(aie::Renderer2D* renderer);

	// Add a behaviour to the agent
	void AddBehaviour(IBehaviour* _behaviour);

	// Movement functions
	void SetPostition(Vector2 _position) { m_MovementInfo.m_Position = _position; }
	Vector2 GetPosition() { return m_MovementInfo.m_Position; }
	void SetVelocity(Vector2 _velocity) { m_MovementInfo.m_Velocity = _velocity; }
	Vector2 GetVelocity() { return m_MovementInfo.m_Velocity; }
	void SetMaxSpeed(float speed) { m_MovementInfo.m_MaxSpeed = speed; }
	float GetMaxSpeed() { return m_MovementInfo.m_MaxSpeed; }
	void AddForce(Vector2 _force) { m_MovementInfo.m_Force = _force + m_MovementInfo.m_Force; }


	MovementInfo m_MovementInfo;

protected:
	Vector2 Truncate(Vector2 _v, float _max);

	std::vector<IBehaviour*> m_BehaviourList;
	IBehaviour* m_CurrentBehaviour;
	

};

