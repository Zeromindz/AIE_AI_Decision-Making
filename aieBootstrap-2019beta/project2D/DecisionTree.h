#pragma once
#include "Agent.h"

// Base decision class
class Decision
{
	void MakeDecision(Agent* _agent, float _deltaTime);
};

// Decision tree node
class DecisionNode : Decision
{
	bool m_Value;
	Decision m_TrueBranch;
	Decision m_FalseBranch;

	void MakeDecision(Agent* _agent, float _deltaTime);

	virtual bool Update(Agent* _agent, float _deltaTime);

};

class DecisionTree
{


};

