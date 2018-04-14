#ifndef LEXICALANALYZER_ANALYZER_H
#define LEXICALANALYZER_ANALYZER_H

#include "State.h"
#include "string"
#include "stream_reader.h"
#include "SymTable.h"
#include "TransitionTable.h"
#include "dfa/DFAState.h"

using namespace std;

typedef string token;
class Analyzer {


public:

    Analyzer(istream &stream, TransitionTable *table,SymTable *symTable);
    // start /analyze
    void start();
    bool restore_last_state();
    token next_token();
    void handle_error();
    bool has_next();

private:
    DFAState *last_accepted_state;
    DFAState *current_state;
    int last_accepted_index;
    int current_index;
    char current_char;
    stream_reader *st_reader;
    string generated_token;
    SymTable *symtable;
    string token_value;
    string lexeme;
    TransitionTable *transition_table;

};


#endif //LEXICALANALYZER_ANALYZER_H
