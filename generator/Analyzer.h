#ifndef LEXICALANALYZER_ANALYZER_H
#define LEXICALANALYZER_ANALYZER_H

#include "State.h"
#include "string"
#include "StreamReader.h"
#include "SymTable.h"
using namespace std;

class Analyzer {


public:

    Analyzer(istream stream);

    typedef string token;

    // start /analyze
    void start(); // input stream??

    bool restore_last_state();

    token *next_token();

    void handle_error();

    string stream_to_string(istream &in);

private:
    State *last_accepted_state;
    State *current_state;
    int last_accepted_index;
    int current_index;
    char current_char;
    stream_reader *st_reader;
    // DFA
    token generated_token;
    SymTable *symtable;
    string token_value;
    //out
};


#endif //LEXICALANALYZER_ANALYZER_H
