#ifndef LEXICALANALYZER_NODE_H
#define LEXICALANALYZER_NODE_H

#include <vector>
#include "Edge.h"

using std::vector;

class Node {
public:
    explicit Node(int id);

    int getID();

    void addChild(Node *child, string edgeValue);

    vector<Edge *> *getChildren();

private:
    int id;
    vector<Edge *> children;
};

#endif