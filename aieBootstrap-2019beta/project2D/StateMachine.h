#pragma once

#include <vector>
#include "Agent.h"
#include "Behaviour.h"

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
class State;
class Condition;

class BaseState
{
public:
    virtual void OnEnter(Agent* _agent) = 0;
    virtual void OnUpdate(Agent* _agent, float _deltaTime) = 0;
    virtual void OnExit(Agent* _agent) = 0;

};

//class PatrolState : BaseState
//{
//    void OnEnter()
//    {
//    }
//
//    void OnUpdate()
//    {
//    }
//
//    void OnExit()
//    {
//    }
//};
//
//enum State
//{
//    STATE_IDLE,
//    STATE_PATROL
//};

class StateMachine : public Behaviour
{
public:    
    StateMachine()
    {
       
    }
    virtual ~StateMachine()
    {
        for (auto state : m_States)
            delete state;
        for (auto c : m_Conditions)
            delete c;
    }

    State* AddState(State* _state)
    {
        m_States.push_back(_state);
        return _state;
    }

    Condition* AddCondition(Condition* _condition)
    {
        m_Conditions.push_back(_condition);
        return _condition;
    }

    void SetCurrentState(State* _state)
    {
        m_CurrentState = _state;
    }

    virtual bool Update(Agent* _agent, float _deltaTime);

protected:
    std::vector<State*> m_States;
    std::vector<Condition*> m_Conditions;

    State* m_CurrentState;
};


