#ifndef LEXICALANALYZER_EDGE_H
#define LEXICALANALYZER_EDGE_H

#include <string>
#include "../../Pattern.h"

using std::string;

/* Cannot not include "Node.h" which already includes "Edge.h".
 * use forward declaration so that the two classes know of each other's existence. */
class Node;

class Edge {
public:
    Edge(Node *destination, Pattern *value);

    Pattern *getValue();

    Node *getDestination();

private:
    Node *destination;
    Pattern *value; // Represent the pattern for a certain transition
};

#endif