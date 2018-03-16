#ifndef LEXICALANALYZER_STATE_H
#define LEXICALANALYZER_STATE_H

#include <vector>

typedef std::pair<char *, State> transition;
typedef std::vector<transition> stateTransitions;

class State {
public:
    State();

    void setID(int id);

    int getID();

    void setAsAccepting();

    bool isAcceptingState();

    void addTransition(transition);

    stateTransitions getTransitions();

private:
    int id;
    bool acceptingState;
    stateTransitions transitions;
};


#endif
