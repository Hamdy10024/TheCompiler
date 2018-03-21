//
// Created by youssef on 18/03/18.
//
#include "SymTable.h"

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

void SymTable ::insert(SymTableEntry entry) {

    entries.push_back(entry);
}
