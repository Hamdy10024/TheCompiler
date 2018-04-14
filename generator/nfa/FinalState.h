#ifndef LEXICALANALYZER_FINALSTATE_H
#define LEXICALANALYZER_FINALSTATE_H

#include "../../new/NFAState.h"
#include <string>
using std::string;

class FinalState : public NFAState {
public:

    using  State::setAsAccepting;
    void setTokenType(string tokenType);

    string getTokenType();

private:
    string tokenType;
};


#endif
