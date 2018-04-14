#ifndef LEXICALANALYZER_STATE_H
#define LEXICALANALYZER_STATE_H

#include <vector>
#include "../generator/Pattern.h"
class State
{

public:
    typedef std::pair<Pattern, State*> transition;
    typedef std::vector<State::transition> stateTransitions;


    State();

    int getID();

    void setID(int);


    void setAsAccepting();

    bool isAcceptingState();

    virtual void addTransition(transition);


    State::stateTransitions *getETransitions();

protected:
    int id; // 0-based, used for indexing the transition table.
    bool acceptingState;
    State::stateTransitions transitions;

};


#endif
