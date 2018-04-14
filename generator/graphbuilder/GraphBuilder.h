#ifndef LEXICALANALYZER_GRAPHBUILDER_H
#define LEXICALANALYZER_GRAPHBUILDER_H

#include "graph/Graph.h"
#include "ThompsonConstructor.h"

static char const CLOSURE = '*';
static char const POSITIVE_CLOSURE = '+';
static char const RANGE = '-';
static char const AND = '.';
static char const OR = '|';

class GraphBuilder {
public:
    Graph *build(char value);

    Graph *build(char rangeBegin, char rangeEnd);

    Graph *build(string);

    Graph *build(Graph *, char operation);

    Graph *build(Graph *, Graph *, char operation);

private:
    ThompsonConstructor thompson;
};

#endif
