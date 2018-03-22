#ifndef LEXICALANALYZER_NODE_H
#define LEXICALANALYZER_NODE_H

#include <vector>
#include "Edge.h"

using std::vector;

class Node {
public:
    void addChild(Edge *edge);

    vector<Edge *> *getChildren();

private:
    vector<Edge *> children;
};

#endif