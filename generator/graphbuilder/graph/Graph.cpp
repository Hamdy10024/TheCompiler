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

void Graph::setEndNode(Node *endNode) {
    this->endNode = endNode;
}

void Graph::connect(Graph *graph) {
    for (auto edge : (*graph->startNode->getChildren()))
        this->endNode->addChild(edge);
    this->endNode = graph->endNode;
    //TODO: delete(graph->startNode);
}
