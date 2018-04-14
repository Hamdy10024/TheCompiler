#ifndef LEXICALANALYZER_EXPRESSIONHANDLER_H
#define LEXICALANALYZER_EXPRESSIONHANDLER_H

#include <bits/stdc++.h>
#include <set>
#include "../graphbuilder/graph/Graph.h"
#include "../graphbuilder/GraphBuilder.h"

using namespace std;

class ExpressionHandler {
public:
    ExpressionHandler();

    Graph *evaluate(string regex);

private:
    static int const MAX_PRECEDENCE = 100;

    unordered_map<char, int> precedence;
    GraphBuilder builder;

    void setPrecedence();

    string insertExplicitConcatenation(string regex);

    string infixToPostfix(string infix);

    int getPrecedence(char c);

    bool contains(set<char> *, char);

    bool isUnaryOperator(char);

    bool isEscapeCharacter(char);
};

#endif
