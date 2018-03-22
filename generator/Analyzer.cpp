#include "Analyzer.h"
#include "SymTable.h"
#include "istream"
#include "StreamReader.h"

Analyzer::Analyzer(istream stream) {
    st_reader = new stream_reader(stream);
    last_accepted_state = NULL;
    last_accepted_index = -1;
    current_index = 0;
    current_state = NULL;
}

void Analyzer::start() {

// just call get_token();
}

void Analyzer::handle_error() {
    printf("error!!\n");
}

token *Analyzer::next_token() {
    bool success;
    current_index = 0;
    last_accepted_state = NULL;
    last_accepted_index = 0;
    while (st_reader->has_next()) {
        current_index++;
        //current_state = dfa.trans[][];    ---> still doesn't know what to do with dfa xD
        st_reader->read();
        //current_index =
        if (current_state->isAcceptingState()) {
            last_accepted_state = current_state;
            last_accepted_index = current_index;
        }
        if (current_state == phi_state) {
            if (restore_last_state()) {
                success = true;
                if (symtable->search_for_token(generated_token)) {
                    // cut substring
                    // add it to symTable

                    symtable->insert(pair<string, string>(token_value, generated_token));
                }
                break;
            } else {
                handle_error();
                success = false;
                break;
            }

        }
    }
    return success == true ? generated_token : NULL;
}

bool Analyzer::restore_last_state() {
    current_state = last_accepted_state;

    // generated_token = current_state.get_token();
    token_value = st_reader->flush_buffer
            ((unsigned int) (last_accepted_index));
    return (current_state == NULL) ? false : true;
}
