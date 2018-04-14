#include "State.h"

State::State()
{
    acceptingState = false;
    id = -2;
}

void State::setID(int id)
{
    this->id = id;
}

int State::getID()
{
    return id;
}

void State::setAsAccepting()
{
    this->acceptingState = true;
}

bool State::isAcceptingState()
{
    return acceptingState;
}

void State::addTransition(transition t)
{
    transitions.push_back(t);
 }

State::stateTransitions * State::getETransitions(){
    return &transitions;
}
