#ifndef LEXICALANALYZER_THOMPSONCONSTRUCTOR_H
#define LEXICALANALYZER_THOMPSONCONSTRUCTOR_H


#include "graph/Graph.h"
#include "../Pattern.h"


class ThompsonConstructor {
public:
    Graph *constructAND(Graph *g1, Graph *g2);

    Graph *constructOR(Graph *g1, Graph *g2);

    Graph *constructCLOSURE(Graph *g);

    Graph *constructPOSITIVE_CLOSURE(Graph *g);
};


#endif
