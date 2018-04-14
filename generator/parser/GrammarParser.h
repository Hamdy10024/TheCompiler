#ifndef LEXICALANALYZER_GRAMMARPARSER_H
#define LEXICALANALYZER_GRAMMARPARSER_H

#include<iostream>
#include<fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "utilities/string.h"
#include "../../new/token_table.h"

using std::vector;
using std::pair;
using std::string;
using std::ifstream;
using std::cout;

class GrammarParser {
public:
    GrammarParser(string fileName, token_table *tokenTable);

    void parse();

    vector<pair<string, string>> *getRegExpressions();

    vector<string> *getKeywords();

    vector<char> *getPunctuations();

private:
    ifstream grammarFile;
    token_table *tokenTable;
    vector<pair<string, string>> regDefs; // Stores <definition, pattern> pairs.
    vector<pair<string, string>> regExps; // Stores <expression, pattern> pairs.
    vector<string> keywords;
    vector<char> punctuations;

    /* checks if the given rule matches any of the language grammar patterns. */
    void isValidRule(string rule);

    void processRule(string rule);

    void updateKeywords(string keywordList);

    void updatePunctuations(string puncList);

    void updateRegulars(string line);

    /* Assuming the regular definition to be replaced was defined earlier (no forward referencing). */
    void replaceDefinitions(string *pattern);
};

#endif
