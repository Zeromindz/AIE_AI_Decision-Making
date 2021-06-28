#pragma once

#include <vector>
#include "Agent.h"

//=========================================================================/
// Decision Making: Short term, moment to moment actions
// Finite State Machines - enums and switch statement
// Finite State Machines - Classes for each state
// Decision Tree
// Behavior Tree
// 
// Planning : Long term, goal - oriented, broad view, How do I win ?
// Goal Oriented Action Planning(GOAP)
// Custom planning algorithm
//_______________________________________________________________/

class BaseState
{
    //BaseState();
    //virtual ~BaseState();
public:
    virtual void OnEnter(Agent* _agent) = 0;
    virtual void OnUpdate(Agent* _agent, float _deltaTime) = 0;
    virtual void OnExit(Agent* _agent) = 0;

};

class PatrolState : BaseState
{
    void OnEnter()
    {
    }

    void OnUpdate()
    {
    }

    void OnExit()
    {
    }
};

enum State
{
    STATE_IDLE,
    STATE_PATROL
};

class StateMachine
{
public:
    void Update()
    {
    }
    void ChangeState(State state)
    {
    }

    State currentState;
    BaseState** stateList;
};


