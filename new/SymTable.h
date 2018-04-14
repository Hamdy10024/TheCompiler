//
// Created by youssef on 18/03/18.
//

#ifndef LEXICALANALYZER_SYMTABLE_H
#define LEXICALANALYZER_SYMTABLE_H

#include "utility"
#include "string"
#include "vector"
#include "map"
using namespace std;

class SymTable {


public:
    SymTable();
    bool search_for_token(string token);
    void insert(pair<string,string>);
    void print_sym_table();
    void insert_into_scanned_list(string token);

private:
    vector<pair<string,string> >entries;
    vector<string> scanned_token_list;  // list of extracted tokens to be inserted in symTable

};


#endif //LEXICALANALYZER_SYMTABLE_H
