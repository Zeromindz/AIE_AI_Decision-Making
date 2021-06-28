#pragma once
#include <Vector>
#include "Vector2.h"
#include "Renderer2D.h"
#include "Texture.h"

class Behaviour;

class Agent
{
public:
	Agent();
	virtual ~Agent();

	// Update the agent and it's behaviour
	virtual void Update(float _deltaTime) = 0;

	// Draw the agent
	virtual void Draw(aie::Renderer2D* renderer) = 0;

	// Add a behaviour to the agent
	void AddBehaviour(Behaviour* _behaviour);

	// Movement functions
	void SetPostition(Vector2 _position) { m_Position = _position; }
	Vector2 GetPosition() { return m_Position; }
	void SetVelocity(Vector2 _velocity) { m_Velocity = _velocity; }
	Vector2 GetVelocity() { return m_Velocity; }
	// TODO - Add _force to m_Force
	void AddForce(Vector2 _force) { m_Force = _force + m_Force; }


private:
	aie::Texture* m_Texture;

	std::vector<Behaviour*> m_BehaviourList;

	Vector2 m_Position = {0, 0};
	Vector2 m_Velocity = {0, 0};
	Vector2 m_Force = {0, 0};

};

