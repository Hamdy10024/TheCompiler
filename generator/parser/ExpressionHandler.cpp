#include "ExpressionHandler.h"
#include <stack>
#include <algorithm>

ExpressionHandler::ExpressionHandler() {
    setPrecedence();
}

Graph *ExpressionHandler::evaluate(string regex) {
    string postfix = infixToPostfix(insertExplicitConcatenation(regex));
    size_t postfixLength = postfix.length();
    set<char> allOperators = {CLOSURE, POSITIVE_CLOSURE, RANGE, AND, OR};
    stack<Graph *> stack;

    for (int i = 0; i < postfixLength; i++) {
        char cur = postfix[i];
        if (!contains(&allOperators, cur)) { // not an operation
            if (isEscapeCharacter(cur)) {
                if(postfix[++i] == 'L')
                    cur = '\0';
                else
                    cur = postfix[i];
            }
            stack.push(builder.build(cur));
        } else {
            Graph *g2 = stack.top();
            stack.pop();
            if (isUnaryOperator(cur)) {
                stack.push(builder.build(g2, cur));
            } else {
                Graph *g1 = stack.top();
                stack.pop();
                stack.push(builder.build(g1, g2, cur));
            }
        }
    }
    return stack.top();
}

void ExpressionHandler::setPrecedence() {
    precedence['*'] = 4; // CLOSURE
    precedence['+'] = 4; // POSITIVE_CLOSURE
    precedence['-'] = 3; // RANGE
    precedence['.'] = 2; // AND
    precedence['|'] = 1; // OR
    precedence['('] = 0;
}

string ExpressionHandler::insertExplicitConcatenation(string regex) {
    char cur, next;
    string newRegex;
    size_t regexLength = regex.length();
    set<char> allOperators = {CLOSURE, POSITIVE_CLOSURE, RANGE, OR};
    set<char> binOperators = {RANGE, OR};

    for (int i = 0; i < regexLength; i++) {
        cur = regex[i];
        if (cur == '.') // decimal point
            newRegex += '\\';
        newRegex += cur;
        if (i + 1 < regexLength) {
            next = regex[i + 1];
            if (cur != '\\' && cur != '(' && next != ')' && !contains(&allOperators, next) &&
                !contains(&binOperators, cur))
                newRegex += AND;
        }
    }
    return newRegex;
}

string ExpressionHandler::infixToPostfix(string infix) {
    string postfix;
    size_t infixLength = infix.length();
    stack<char> stack;
    for (int i = 0; i < infixLength; i++) {
        char cur = infix[i];
        switch (cur) {
            case '(':
                stack.push(cur);
                break;

            case ')':
                while (stack.top() != '(') {
                    postfix += stack.top();
                    stack.pop();
                }
                stack.pop();
                break;

            case '\\':
                postfix += cur;
                postfix += infix[++i];
                break;

            default:
                while (!stack.empty()) {
                    if (getPrecedence(stack.top()) >= getPrecedence(cur)) {
                        postfix += stack.top();
                        stack.pop();
                    } else {
                        break;
                    }
                }
                stack.push(cur);
        }
    }
    while (!stack.empty()) {
        postfix += stack.top();
        stack.pop();
    }
    return postfix;
}

int ExpressionHandler::getPrecedence(char c) {
    unordered_map<char, int>::const_iterator i = precedence.find(c);
    return (i == precedence.end()) ? MAX_PRECEDENCE : i->second;
}

bool ExpressionHandler::contains(set<char> *opSet, char op) {
    return find((*opSet).begin(), (*opSet).end(), op) != (*opSet).end();
}

bool ExpressionHandler::isUnaryOperator(char op) {
    return op == CLOSURE || op == POSITIVE_CLOSURE;
}

bool ExpressionHandler::isEscapeCharacter(char c) {
    return c == '\\';
}