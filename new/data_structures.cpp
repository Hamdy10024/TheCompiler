#include "token_table.h"
bool token_table::insert_token(Token token) {
        for (int i=0;i<token_tab.size();i++)
            if(token_tab[i] == token)
                return false;
        token_tab.push_back(token);
        return true;
    }
Token token_table::token_at(int i) {
        if (i >= token_tab.size())
            return token_table::empty_token;
        return token_tab[i];

    }
Token token_table::empty_token = "";

bool token_table::insert_keyword(Token key) {
for (int i=0;i<key_tab.size();i++)
            if(key_tab[i] == key)
                return false;
        key_tab.push_back(key);
        return true;
}
int token_table::compare_priority(Token a,Token b) {


    if(a=="" && b=="")
        return  0;
    if(a=="")
        return 1;
    if(b=="")
        return -1;

    for (int i = 0; i < key_tab.size(); i++)
    {       if (key_tab[i] == a)
            return -1;
        else if (key_tab[i] == b)
            return 1;
}
        for (int i=0;i<token_tab.size();i++) {
            cout<<"comparing "<<token_tab[i] <<" "<<a<<" "<<b<<endl;
            if (token_tab[i] == a)
                return -1;
            else if (token_tab[i] == b)
                return 1;
        }
            return 0;
}
