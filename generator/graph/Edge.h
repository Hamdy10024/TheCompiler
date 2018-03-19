#ifndef LEXICALANALYZER_EDGE_H
#define LEXICALANALYZER_EDGE_H

#include <string>

using std::string;

/* Cannot not include "Node.h" which already includes "Edge.h".
 * use forward declaration so that the two classes know of each other's existence. */
class Node;

class Edge {
public:
    Edge(Node *destination, string value);

    string getValue();

    Node *getDestination();

private:
    Node *destination;
    string value;
};


#endif