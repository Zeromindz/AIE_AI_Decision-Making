#pragma once
#include "Agent.h"

class Behaviour
{
public:
	// Empty constructors and destructors for base class
	Behaviour();
	virtual ~Behaviour();

	// Pure virtual function for executing the behaviour
	virtual bool Update(Agent* _agent, float _deltaTime) { return true; }
	virtual bool Update(Agent* _agent, std::vector<Vector2> _path, float _deltaTime) { return true; }

private:

};

