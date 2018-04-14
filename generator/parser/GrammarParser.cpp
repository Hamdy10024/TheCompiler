#include "GrammarParser.h"

GrammarParser::GrammarParser(string fileName, token_table *tokenTable) : grammarFile(fileName) {
    this->tokenTable = tokenTable;
}

void GrammarParser::parse() {
    string line;
    if (grammarFile.is_open()) {
        while (getline(grammarFile, line)) {
            // check that the rule matches one of the given formats first, or return error o.w
            processRule(line);
        }
    } else {
        //TODO: Add 'ErrorHandler' class
        cout << "ERROR: COULD NOT OPEN GRAMMAR FILE!\n";
        return;
    }
}

vector<pair<string, string>> *GrammarParser::getRegExpressions() {
    return &regExps;
}

vector<string> *GrammarParser::getKeywords() {
    return &keywords;
}

vector<char> *GrammarParser::getPunctuations() {
    return &punctuations;
}

void GrammarParser::isValidRule(string rule) {

}

void GrammarParser::processRule(string rule) {
    int i = 0;
    for (; i < rule.length(); ++i)
        if (!isBlankSpace(rule[i]))
            break;
    if (rule[i] == '{')
        updateKeywords(rule);
    else if (rule[i] == '[')
        updatePunctuations(rule);
    else
        updateRegulars(rule);
}

void GrammarParser::updateKeywords(string keywordList) {
    int i = 0;
    size_t listLength = keywordList.length();
    while (i < listLength) {
        if (isBlankSpace(keywordList[i]) || keywordList[i] == '{') {
            i++;
        } else {
            int j = i;
            string keyword;
            while (j < listLength && !isBlankSpace(keywordList[j]) && keywordList[j] != '}')
                keyword += keywordList[j++];
            keywords.push_back(keyword);
            tokenTable->insert_keyword(keyword);
            i = j + 1;
        }
    }
}

void GrammarParser::updatePunctuations(string puncList) {
    int i = 0;
    size_t listLength = puncList.length();
    while (i < listLength) {
        if (!(isBlankSpace(puncList[i]) || puncList[i] == '[' || puncList[i] == ']' || puncList[i] == '\\')) {
            punctuations.push_back(puncList[i]);
            tokenTable->insert_keyword(string(1, puncList[i]));
        }
        i++;
    }
}

void GrammarParser::updateRegulars(string line) {
    string regName, pattern;
    bool def = false;
    int i = 0;
    while (line[i] != '=' && line[i] != ':')
        copyNonBlank(line, &regName, i++);
    if (line[i] == '=')
        def = true;
    i++;
    while (i < line.length())
        copyNonBlank(line, &pattern, i++);
    replaceDefinitions(&pattern);
    if (def)
        regDefs.push_back(make_pair(regName, pattern));
    else {
        regExps.push_back(make_pair(regName, pattern));
        cout<<"sorry "<<tokenTable->insert_token(regName)<<endl;
    }
}

//TODO: Optimize
void GrammarParser::replaceDefinitions(string *pattern) {
    for (int i = regDefs.size() - 1; i >= 0; --i) {
        pair<string, string> regDef = regDefs[i];
        string regDefPattern = '(' + regDef.second + ')';
        size_t regDefLength = regDefPattern.length();
        unsigned long pos = (*pattern).find(regDef.first);
        while (pos != string::npos) {
            (*pattern).replace(pos, regDef.first.length(), regDefPattern);
            pos = (*pattern).find(regDef.first, pos + regDefLength);
        }
    }
}