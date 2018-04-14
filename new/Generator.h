
#ifndef LEXICALANALYZER_GENERATOR_H
#define LEXICALANALYZER_GENERATOR_H

#include <string>
#include "Analyzer.h"

using std::string;

class Generator {
public:
    Generator(string fileName);
    Analyzer * generate(string is);
    string filename;
};


#endif
