#include "Analyzer.h"
#include "SymTable.h"
Analyzer::Analyzer() {

    last_accepted_state = NULL;
    last_accepted_index = -1;
    current_index = 0;
    current_state = NULL;
    start_index=0;
    end_index=0;

}

void Analyzer::start() {
/*
  // init stream :
  TODO add class stream
*/
}

void Analyzer::handle_error() {

}

token * Analyzer::next_token() {
    bool success;
    start_index = end_index;

/*
    // while stream.hasNext() {
    //current_index++;
     current_state = dfa.trans[][];
     current_index =
     if (current_state.isAcceptingState()){
        last_accepted_state = current_state;
        last_accepted_index = current_index;

     }
     if (current_state ==phi_state){
        if(restore_last_state()){
        success = true;
        if (search_for_token(generated_token)){

        // cut substring
        // construct SymTableEntry
        // add it to symTable
        }
        break;
        }
        else {
            //handle_error();
            success=false;

            break;
        }

     }
    }
    return success==true?generated_token :NULL;
*/

}

bool Analyzer::restore_last_state() {
    current_state = last_accepted_state;
    current_index = last_accepted_index;
    end_index = current_index;
    // generated_token = current_state.get_token();

    return (current_state==NULL) ?false : true;
}
