#pragma once
#include "Agent.h"

class Behaviour
{
public:
	// Empty constructors and destructors for base class
	Behaviour() {}
	virtual ~Behaviour() {}

	// Virtual update function for executing the behaviour
	virtual bool Update(Agent* _agent, float _deltaTime) = 0;
	// Overloaded virtual update function using the calculated path as a param
	//virtual bool Update(Agent* _agent, std::vector<Vector2> _path, float _deltaTime) { return true; }

private:

};

