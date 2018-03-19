#ifndef LEXICALANALYZER_GRAPH_H
#define LEXICALANALYZER_GRAPH_H

#include "Node.h"

class Graph {
public:
    explicit Graph(Node *startNode);

    Node *getStartNode();

    Node *getEndNode();

    void connect(Graph *graph);

private:
    Node *startNode;
    Node *endNode;
};

#endif