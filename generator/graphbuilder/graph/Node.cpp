#include "Node.h"

void Node::addChild(Edge *edge) {
    children.push_back(edge);
}

vector<Edge *> *Node::getChildren() {
    return &children;
}