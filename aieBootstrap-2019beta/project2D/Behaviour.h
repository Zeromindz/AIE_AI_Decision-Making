#pragma once
#include "Agent.h"

class Behaviour
{
public:
	// Empty constructors and destructors for base class
	Behaviour();
	virtual ~Behaviour();

	// Pure virtual function for executing the behaviour
	virtual bool Update(Agent* _agent, float _deltaTime) = 0;

private:

};

