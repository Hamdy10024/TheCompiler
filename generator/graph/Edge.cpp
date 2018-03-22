#include "Edge.h"

Edge::Edge(Node *destination, Pattern *value) {
    this->destination = destination;
    this->value = value;
}

Pattern *Edge::getValue() {
    return value;
}

Node *Edge::getDestination() {
    return destination;
}
