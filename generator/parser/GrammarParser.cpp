#include "GrammarParser.h"

GrammarParser::GrammarParser(string fileName) : grammarFile(fileName) {}

GrammarParser::~GrammarParser() {}

void GrammarParser::processGrammar() {
    string line;
    if (grammarFile.is_open()) {
        while (getline(grammarFile, line)) {
            // check that the rule matches one of the given formats first, or return error o.w
            processRule(line);
        }
        for (auto &regDef : regDefs)
            cout << regDef.first << "\t" << regDef.second << "\n";

        for (int j = 0; j < regExps.size(); ++j)
            cout << regExps[j].first << "\t" << regExps[j].second << "\n";
    } else {
        //TODO: Add 'ErrorHandler' class
        cout << "ERROR: COULD NOT OPEN GRAMMAR FILE!\n";
        return;
    }
}

void GrammarParser::isValidRule(string rule) {

}

void GrammarParser::processRule(string rule) {
    if (rule[0] == '{')
        updateKeywords(rule);
    else if (rule[0] == '[')
        updatePunctuations(rule);
    else
        updateRegulars(rule);
}

void GrammarParser::updateKeywords(string keywordlist) {

}

void GrammarParser::updatePunctuations(string puncList) {

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
    else
        regExps.push_back(make_pair(regName, pattern));
}

//TODO: Optimize
void GrammarParser::replaceDefinitions(string *pattern) {
    for (int i = regDefs.size() - 1; i >= 0; --i) {
        pair<string, string> regDef = regDefs[i];
        string regDefPattern = '(' + regDef.second + ')';
        size_t regDefLength = regDefPattern.length();
        unsigned long pos = (*pattern).find(regDef.first);
        while(pos != string::npos) {
            (*pattern).replace(pos, regDef.first.length(), regDefPattern);
            pos = (*pattern).find(regDef.first, pos + regDefLength);
        }
    }
}