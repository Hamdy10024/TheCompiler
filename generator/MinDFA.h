#ifndef LEXICALANALYZER_MINDFA_H
#define LEXICALANALYZER_MINDFA_H

#include <vector>
#include "State.h"

class MinDFA {
public:
    typedef std::vector<State::stateTransitions> table;

    MinDFA();


private:
};

#endif
