#include "GraphBuilder.h"

Graph *GraphBuilder::build(char value) {
    Node *startNode = new Node();
    Node *endNode = new Node();
    Graph *g = new Graph(startNode);
    startNode->addChild(new Edge(endNode, new Pattern(value)));
    g->setEndNode(endNode);
    return g;
}

Graph *GraphBuilder::build(char rangeBegin, char rangeEnd) {
    Node *startNode = new Node();
    Node *endNode = new Node();
    Graph *g = new Graph(startNode);
    startNode->addChild(new Edge(endNode, new Pattern(rangeBegin, rangeEnd)));
    g->setEndNode(endNode);
    return g;
}

Graph *GraphBuilder::build(string pattern) {
    Node *startNode = new Node();
    Node *cur = startNode;
    Graph *g = new Graph(startNode);
    for (auto c : pattern) {
        Node *next = new Node();
        cur->addChild(new Edge(next, new Pattern(c)));
        cur = next;
    }
    g->setEndNode(cur);
    return g;
}

Graph *GraphBuilder::build(Graph *g, char operation) {
    switch (operation) {
        case CLOSURE:
            return thompson.constructCLOSURE(g);
        case POSITIVE_CLOSURE:
            return thompson.constructPOSITIVE_CLOSURE(g);
        default:
            return nullptr;
    }
}

Graph *GraphBuilder::build(Graph *g1, Graph *g2, char operation) {
    switch (operation) {
        case RANGE:
            return build((*g1->getStartNode()->getChildren())[0]->getValue()->get(),
                         (*g2->getStartNode()->getChildren())[0]->getValue()->get());
        case AND:
            return thompson.constructAND(g1, g2);
        case OR:
            return thompson.constructOR(g1, g2);
        default:
            return nullptr;
    }
}
