#pragma once
#include <vector>
#include "Vector2.h"
class Agent;
class MovementInfo;

class IBehaviour
{
public:
	IBehaviour() {}
	virtual ~IBehaviour() = 0 {}

	virtual void Update(Agent* _agent, float _deltaTime, MovementInfo& _behaviour) {}
		 
private:

};

