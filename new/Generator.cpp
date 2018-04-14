//
// Created by abeer on 3/24/18.
//

#include <fstream>
#include "Generator.h"
#include "iostream"
#include "token_table.h"
#include "../generator/parser/GrammarParser.h"
#include "../generator/nfa/NFA.h"
#include "DFA.h"

using  namespace std;

Generator::Generator(string fileName) {
this->filename = fileName;
}
Analyzer * Generator::generate(string is) {
    token_table *tokenTable = new token_table();
    ifstream myReadFile;
    myReadFile.open(is);
    GrammarParser *parser = new GrammarParser(filename, tokenTable);
    parser->parse();

    NFA *nfa = new NFA(parser->getRegExpressions(), parser->getKeywords(), parser->getPunctuations());
    nfa->combineNFA();
    NFAState *startState = nfa->getStartState();


    SymTable *symtab = new SymTable();
    for (int i=0;i<tokenTable->token_tab.size();i++)
        symtab->insert_into_scanned_list(tokenTable->token_at(i));
    DFA *dfa = new DFA (startState,tokenTable);

    TransitionTable *table;
    table = dfa->getTable();
    stringstream fortest;
    fortest <<"int while 098 xyz,x<2.3,float";
    // table->print();
    Analyzer * analyzer = new Analyzer(myReadFile,table,symtab);
    return analyzer;
}