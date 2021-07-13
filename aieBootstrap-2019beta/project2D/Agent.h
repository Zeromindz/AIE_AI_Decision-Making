#pragma once
#include <Vector>
#include "Vector2.h"
#include "Renderer2D.h"
#include "DynamicObject.h"

class IBehaviour;

class Agent : public DynamicObject
{
public:
	Agent();
	Agent(float _posX, float _posY);
	virtual ~Agent();

	virtual void Update(float _deltaTime);
	virtual void Draw(aie::Renderer2D* _renderer);

	// Add a behaviour to the agent
	void AddBehaviour(IBehaviour* _behaviour);

protected:
	Vector2 Truncate(Vector2 _v, float _max);
	IBehaviour* m_CurrentBehaviour = nullptr;

	//std::vector<IBehaviour*> m_BehaviourList;
	

};

