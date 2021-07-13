#pragma once
#include <vector>
#include "Vector2.h"
#include "Renderer2D.h"

class Agent;

class IBehaviour
{
public:
	IBehaviour() {}
	virtual ~IBehaviour() = 0 {}

	virtual void Update(Agent* _agent, float _deltaTime) {}
	virtual void DebugDraw(Agent* _agent, aie::Renderer2D* _renderer) {}
		 
private:
};

