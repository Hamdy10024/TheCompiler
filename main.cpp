#include <iostream>
#include "generator/State.h"
#include "generator/MinDFA.h"
#include "generator/TransitionTable.h"
#include "generator/graph/Graph.h"

int main() {
    Node *startNode = new Node(0);
    Graph *g1 = new Graph(startNode);

    g1->getStartNode()->addChild(new Node(1), "ToNode1");
    g1->getStartNode()->addChild(new Node(2), "ToNode2");

    Graph *g2 = new Graph(new Node(3));
    g1->connect(g2);

    /*std::cout << "StartNode: " << g1->getStartNode()->getID() << std::endl;
    std::cout << "EndNode: " << g1->getEndNode()->getID() << std::endl;*/

    // std::cout << "Number of Children: " << g1->getStartNode()->getChildren()->size()<< std::endl;

    for (int i = 0; i < g1->getStartNode()->getChildren()->size(); ++i) {
        std::cout << "Edge: " << (*g1->getStartNode()->getChildren())[i]->getValue() << std::endl;
    }

    delete(startNode);
    delete(g1);
    delete(g2);

    std::cout << "StartNode: " << startNode->getID() << std::endl; // no error!!

    std::cout << "Hello, World!" << std::endl;
    return 0;
}