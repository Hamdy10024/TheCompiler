//
// Created by youssef on 18/03/18.
//

#ifndef LEXICALANALYZER_SYMTABLE_H
#define LEXICALANALYZER_SYMTABLE_H

#include "utility"
#include "string"
#include "vector"

using namespace std;

class SymTable {


/*public:
    SymTable();

    bool insert(SymTableEntry);

    SymTableEntry look_up();

//add size
private:
    vector<SymTableEntry> entries;*/
};


class SymTableEntry {
    enum scope {
        global, local
    };
public:
    pair<string, string> token;
    scope scope;
    int line;
};

#endif //LEXICALANALYZER_SYMTABLE_H
