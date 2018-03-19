#include "Edge.h"

Edge::Edge(Node *destination, string value) {
    this->destination = destination;
    this->value = value;
}

string Edge::getValue() {
    return value;
}

Node *Edge::getDestination() {
    return destination;
}