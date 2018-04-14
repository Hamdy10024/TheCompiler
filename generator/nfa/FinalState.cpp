#include "FinalState.h"

void FinalState::setTokenType(string tokenType) {
    this->tokenType = tokenType;
    this->tk = tokenType;

    acceptingState = tokenType.size() > 0;
}

string FinalState::getTokenType() {
    return tokenType;
}
