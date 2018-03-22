#ifndef LEXICALANALYZER_STATE_H
#define LEXICALANALYZER_STATE_H

#include <vector>

class State {
public:
    typedef std::pair<char *, State> transition;

    typedef std::vector<State::transition> stateTransitions;

    State();

    void setID(int id);

    int getID();

    void setAsAccepting();

    bool isAcceptingState();

    void addTransition(transition);

    State::stateTransitions getTransitions();

private:
    int id; // 0-based, used for indexing the transition table.
    bool acceptingState;
    State::stateTransitions transitions;
};


#endif
