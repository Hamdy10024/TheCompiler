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

   // SymTableEntry look_up();   ----> will be needed in parser phase isA

//add size
private:
    vector<pair<string,string> >entries;
    vector<string> scanned_token_list;  // list of extracted tokens to be inserted in symTable
};

//
//class SymTableEntry {
//    enum scope {
//        global, local
//    };
//public:
//    pair<string, string> token;
////    scope scope;
////    int line;
//};

#endif //LEXICALANALYZER_SYMTABLE_H
