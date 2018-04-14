/*
 * File:   NFAState.h
 * Author: Abeer
 *
 * Created on March 21, 2018, 1:02 AM
 */

#ifndef NFASTATE_H
#define NFASTATE_H

#include <vector>
#include "Entry.h"
#include "headers.h"
#include "State.h"
class NFAState : public State
{

	typedef std::pair <Pattern *,NFAState*> move;

	typedef std::vector<NFAState::move> stateMoves;
public:
    NFAState() {
	}
    NFAState(int id);
    void setAsAccepting(Token tk);
    Token getToken();
	void addTransition(move);
	void  addTransition(transition);
	NFAState:: stateMoves *getTransitions();
	NFAState::stateMoves moves;
protected:

    Token tk;
};

#endif /* NFASTATE_H */
