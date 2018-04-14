#ifndef LEXICALANALYZER_MINDFA_H
#define LEXICALANALYZER_MINDFA_H
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include "State.h"
#include "dfa/DFAState.h"
#include "TransitionTable.h"
using namespace std;
typedef int Class;
class MinDFA
{
private:
        map <Pattern,int> entr_row;
        map<State *,Class> states;
        map<Token,int> token_row;
        vector<Pattern> referenc;
        vector <State*> all_states;
public:

    MinDFA();
    void create_basis(TransitionTable::table &tab);
    TransitionTable* minimize(TransitionTable::table &tab,State * start);
    TransitionTable* create_min_graph(int b,State *start);
private:
};

#endif
