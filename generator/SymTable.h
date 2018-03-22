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

    bool search_for_token(string token);

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
    vector<string> scanned_token_list;  // list of extracted tokens to be inserted in symTable
    scope scope;
    int line;
};

#endif //LEXICALANALYZER_SYMTABLE_H
