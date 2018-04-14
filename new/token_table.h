#ifndef TOKEN_TABLE_H_INCLUDED
#define TOKEN_TABLE_H_INCLUDED
#include "headers.h"
#include <string>
#include <vector>

class token_table {
private :

    std::vector<Token> key_tab;
public :
    static Token empty_token;

    std::vector<Token> token_tab;
   ///returns false if exists
    bool insert_token(Token);
    /// return empty token at out of dimension
    Token token_at(int);

bool insert_keyword(Token);

int compare_priority(Token,Token);

};

#endif // TOKEN_TABLE_H_INCLUDED
