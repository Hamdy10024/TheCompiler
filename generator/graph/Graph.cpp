#include <iostream>
#include "Graph.h"

Graph::Graph(Node *startNode) {
    this->startNode = startNode;
    this->endNode = startNode;
}

Node *Graph::getStartNode() {
    return startNode;
}

Node *Graph::getEndNode() {
    return endNode;
}

void Graph::connect(Graph *graph) {
    this->endNode->addChild(graph->startNode, "LAMBDA");
    this->endNode = graph->endNode;
}