#ifndef LEXICALANALYZER_GRAMMARPARSER_H
#define LEXICALANALYZER_GRAMMARPARSER_H

#include<iostream>
#include<fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "utilities/string.h"

using std::vector;
using std::pair;
using std::string;
using std::ifstream;
using std::cout;

class GrammarParser {
public:
    explicit GrammarParser(string fileName);

    ~GrammarParser();

    /* get NFAs */

private:
    enum RULE_TYPE {
        REGULAR_DEFINITION,
        REGULAR_EXPRESSION,
        KEYWORD_DEFINITION,
        PUNCTUATION_DEFINTION
    };

    ifstream grammarFile;

    vector<pair<string, string>> regDefs; // Stores <definition, pattern> pairs.

    vector<pair<string, string>> regExps; // Stores <expression, pattern> pairs.
public:
    void processGrammar();

    /* checks if the given rule matches any of the language grammar patterns. */
    void isValidRule(string rule);

    void processRule(string rule);

    void updateKeywords(string keywordlist);

    void updatePunctuations(string puncList);

    void updateRegulars(string line);

    /* Assuming the regular definition to be replaced was defined earlier (no forward referencing). */
    void replaceDefinitions(string *pattern);
};

#endif
