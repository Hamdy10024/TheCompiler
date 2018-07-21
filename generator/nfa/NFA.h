#ifndef LEXICALANALYZER_NFA_H
#define LEXICALANALYZER_NFA_H

#include "../graphbuilder/GraphBuilder.h"
#include "../parser/ExpressionHandler.h"
#include "NFAState.h"
#include <queue>

class NFA {
public:

    typedef std::vector<NFAState *> table;

    NFA(vector<pair<string, string>> *expressions, vector<string> *keywords, vector<char> *punctuations);

    void combineNFA(); // Transforms graph nodes to NFAStates with their transitions

    NFAState *getStartState();

private:
    GraphBuilder builder;
    ExpressionHandler expHandler;

    /* Vectors of <Token : NFA> pairs */
    vector<pair<string, Graph *>> expNFAGraphs;
    vector<pair<string, Graph *>> keywordNFAGraphs;
    vector<pair<string, Graph *>> puncNFAGraphs;

    /* Combined NFA */
    table transTable;
    NFAState *startState;

    void buildExpNFAs(vector<pair<string, string>> *expressions);

    void buildKeywordNFAs(vector<string> *keywords);

    void buildPuncNFAs(vector<char> *punctuations);

    void graphToNFA(string tokenType, Graph *g);
};

#endif
