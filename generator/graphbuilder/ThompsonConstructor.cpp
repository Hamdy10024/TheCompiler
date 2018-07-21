#include <headers.h>
#include "ThompsonConstructor.h"

Graph *ThompsonConstructor::constructAND(Graph *g1, Graph *g2) {
    g1->connect(g2);
    return g1;
}

Graph *ThompsonConstructor::constructOR(Graph *g1, Graph *g2) {
    Node *orStart = new Node();
    Node *orEnd = new Node();
    Graph *orGraph = new Graph(orStart);

    orStart->addChild(new Edge(g1->getStartNode(), new Pattern(LAMBDA)));
    orStart->addChild(new Edge(g2->getStartNode(), new Pattern(LAMBDA)));

    g1->getEndNode()->addChild(new Edge(orEnd, new Pattern(LAMBDA)));
    g2->getEndNode()->addChild(new Edge(orEnd, new Pattern(LAMBDA)));

    orGraph->setEndNode(orEnd);
    // delete g1, g2

    return orGraph;
}

Graph *ThompsonConstructor::constructCLOSURE(Graph *g) {
    Node *closureStart = new Node();
    Node *closureEnd = new Node();
    Graph *closureGraph = new Graph(closureStart);

    closureStart->addChild(new Edge(g->getStartNode(), new Pattern(LAMBDA)));
    closureStart->addChild(new Edge(closureEnd, new Pattern(LAMBDA)));

    g->getEndNode()->addChild(new Edge(g->getStartNode(), new Pattern(LAMBDA)));
    g->getEndNode()->addChild(new Edge(closureEnd, new Pattern(LAMBDA)));

    closureGraph->setEndNode(closureEnd);
    // delete g

    return closureGraph;
}

Graph *ThompsonConstructor::constructPOSITIVE_CLOSURE(Graph *g) {
    Node *closureStart = new Node();
    Node *closureEnd = new Node();
    Graph *closureGraph = new Graph(closureStart);

    closureStart->addChild(new Edge(g->getStartNode(), new Pattern(LAMBDA)));

    g->getEndNode()->addChild(new Edge(g->getStartNode(), new Pattern(LAMBDA)));
    g->getEndNode()->addChild(new Edge(closureEnd, new Pattern(LAMBDA)));

    closureGraph->setEndNode(closureEnd);
    // delete g

    return closureGraph;
}
