#include "Analyzer.h"
#include "dfa/DFAState.h"
Analyzer::Analyzer(istream &stream, TransitionTable *table,SymTable *sTable) {
    transition_table = table;
    st_reader = new stream_reader(stream);
    last_accepted_state = NULL;
    last_accepted_index = -1;
    current_index = 0;
    current_state = NULL;
    this->symtable = sTable;

}

void Analyzer::start() {

// just call get_token();
}

void Analyzer::handle_error() {
    printf("Error!! \n");
}

token Analyzer::next_token() {
    bool success= false;
    current_index = 0;
    last_accepted_state = NULL;
    last_accepted_index = 0;

    current_state = (DFAState*)transition_table->getStartState();
    while (st_reader->has_next()) {
        current_index++;
        char ch = st_reader->read();
        if (ch == ' '|| ch=='\n' || ch=='\t')
            continue;
        current_state =(DFAState*) transition_table->getNextState(current_state, ch);

        if (current_state == NULL) {
            if (restore_last_state()) {
                success = true;
                if (symtable->search_for_token(generated_token)) {
                    symtable->insert(pair<string, string>(token_value, generated_token));
                }
                break;
            } else {
                handle_error();
                st_reader->flush_buffer();
                success = false;
                break;
            }
        }
        else if (current_state->getToken().size() > 0) {
            last_accepted_state = current_state;
            last_accepted_index = current_index;

        }

    }
    return success == true ? generated_token : "";
}

bool Analyzer::restore_last_state() {
    current_state = last_accepted_state;
    token_value = st_reader->flush_buffer
            ((unsigned int) (last_accepted_index));

    generated_token = (current_state!=NULL) ? (current_state)->getToken():"";
    lexeme = token_value;
    return (current_state == NULL) ? false : true;
}
bool Analyzer::has_next() {
    return st_reader->has_next();
}
