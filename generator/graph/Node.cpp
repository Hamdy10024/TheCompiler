#include "Node.h"

Node::Node(int id) {
    this->id = id;
}

void Node::addChild(Node *child, string edgeValue) {
    children.push_back(new Edge(child, edgeValue));
}

vector<Edge *> *Node::getChildren() {
    return &children;
}

int Node::getID() {
    return id;
}