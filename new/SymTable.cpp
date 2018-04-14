//
// Created by youssef on 18/03/18.
//
#include "SymTable.h"
#include "iostream"
SymTable ::SymTable() {

}

bool SymTable::search_for_token(string token) {

    for (int i =0;i<scanned_token_list.size();i++){
        if (scanned_token_list[i]==token){
            return true;
        }
    }
    return false;
}

void SymTable::insert(pair<string,string> entry) {
    entries.push_back(entry);

}

void  SymTable::print_sym_table(){
    cout <<"printing symtable "<< endl;
    for (int i =0;i<entries.size();i++){
        cout<<"lexeme  " <<entries[i].first << "   token  " << entries[i].second <<endl;
    }
}

void SymTable::insert_into_scanned_list(string token){
    scanned_token_list.push_back(token);
}
