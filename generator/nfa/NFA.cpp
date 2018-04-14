#include "NFA.h"
#include "../../new/State.h"
#include "FinalState.h"

NFA::NFA(vector<pair<string, string>> *expressions, vector<string> *keywords, vector<char> *punctuations) {
    buildExpNFAs(expressions);
    buildKeywordNFAs(keywords);
    buildPuncNFAs(punctuations);
}

void NFA::combineNFA() {
    startState = new NFAState();
    startState->setID(0);
    for (auto pair : keywordNFAGraphs)
        graphToNFA(pair.first, pair.second);

    for (auto pair : expNFAGraphs)
        graphToNFA(pair.first, pair.second);

    for (auto pair : puncNFAGraphs)
        graphToNFA(pair.first, pair.second);
}

NFAState *NFA::getStartState() {
    return startState;
}

void NFA::buildExpNFAs(vector<pair<string, string>> *expressions) {
    for (auto exp : *expressions)
        expNFAGraphs.push_back(make_pair(exp.first, expHandler.evaluate(exp.second)));
}

void NFA::buildKeywordNFAs(vector<string> *keywords) {
    for (auto keyword : *keywords)
        keywordNFAGraphs.push_back(make_pair(keyword, builder.build(keyword)));
}

void NFA::buildPuncNFAs(vector<char> *punctuations) {
    for (auto punctuation : *punctuations)
        puncNFAGraphs.push_back(make_pair(string(1, punctuation), builder.build(punctuation)));
}

void NFA::graphToNFA(string tokenType, Graph *g) {
    unordered_map<Node *, NFAState *> visited; // Keep track of all nodes that have already been visited (cloned into NFAStates)
    queue<Node *> q;
    static int counter =1;
    Node *cur = g->getStartNode();
    NFAState *state = new NFAState(); // Clone start node
    state->setID(counter++);
    visited[cur] = state; // Mark node as visited (cloned into NFAState)
    q.push(cur);

    startState->addTransition(make_pair(new Pattern(LAMBDA), state)); // Connect start state to the current NFA

    while (!q.empty()) {
        cur = q.front(); // Get the front node and visit all its children
        q.pop();
        vector<Edge *> *children = cur->getChildren();
        size_t n = children->size();

        for (int i = 0; i < n; i++) {
            Edge *edge = (*children)[i];
            Node *child = edge->getDestination();
            if (child->getChildren()->empty()) { // Check if end node
                FinalState *final = new FinalState();
                final->setID(counter++);
                final->setAsAccepting();
                final->setTokenType(tokenType);
                visited[child] = final;
            }
            else if (visited[child] == nullptr) { // Check if the current node has already been cloned
                state = new NFAState(); // If not, create a new NFAState and add it tp the map
                state->setID(counter++);
                visited[child] = state;
                q.push(child);
            }
            visited[cur]->addTransition(make_pair(edge->getValue(), visited[child])); // Add these children (transitions) to the cloned NFAState
        }
    }
}