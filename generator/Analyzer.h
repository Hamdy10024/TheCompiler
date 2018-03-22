#ifndef LEXICALANALYZER_ANALYZER_H
#define LEXICALANALYZER_ANALYZER_H

#include "State.h"
#include "string"

using namespace std;

class Analyzer {


public:

    Analyzer();

    typedef string token;

    // start /analyze
    void start(); // input stream??

    bool restore_last_state();

    token *next_token();

    void handle_error();

private:
    int start_index;
    int end_index;      // start and end indices used to get lexemes
    State *last_accepted_state;
    State *current_state;
    int last_accepted_index;
    int current_index;
    char current_char;
    // DFA
    token generated_token;
    //symtable
    //out
};


#endif //LEXICALANALYZER_ANALYZER_H
