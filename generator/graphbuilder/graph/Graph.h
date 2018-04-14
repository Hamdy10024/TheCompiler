#ifndef LEXICALANALYZER_GRAPH_H
#define LEXICALANALYZER_GRAPH_H

#include "Node.h"

class Graph {
public:
    Graph(Node *startNode);

    Node *getStartNode();

    Node *getEndNode();

    void setEndNode(Node *endNode);

    void connect(Graph *graph);

private:
    Node *startNode;
    Node *endNode;
};

#endif