#pragma once
#include "Behaviour.h"

// The Condition class is another abstract base class. 
// We’ll need to sub-class this for each unique condition that we need.
// Sub-classing the Behaviour class will allow us to reuse these Condition classes later
// It also means we must override the Update() method of the Behaviour class, returning the result of our test.
// Each Condition sub-class will override the test function, implementing whatever test is required.
// We'll also create new constructors for the sub-classes to ensure the condition is initialized with whatever data needed to perform the test
class Condition : public Behaviour
{
public:
	Condition() {}
	virtual ~Condition() {}

	virtual bool Test(Agent* _agent) const = 0;

	virtual bool Update(Agent* _agent, float _deltaTime)
	{
		if (Test(_agent))
		{
			return true;
		}
		return false;
	}

private:

};

class WithinRangeCondition : public Condition
{
public:
	WithinRangeCondition(Agent* _target, float _range)
	{
		m_Target = _target;
		m_Range = _range;
	}

	virtual ~WithinRangeCondition() {}

	virtual bool Test(Agent* _agent) const;

private:
	Agent* m_Target;
	float m_Range;
};

