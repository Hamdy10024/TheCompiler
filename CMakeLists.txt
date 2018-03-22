cmake_minimum_required(VERSION 3.8)
project(LexicalAnalyzer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp generator/State.cpp generator/State.h generator/MinDFA.cpp generator/MinDFA.h generator/TransitionTable.cpp generator/TransitionTable.h generator/SymTable.h generator/SymTable.cpp generator/graph/Graph.cpp generator/graph/Graph.h generator/graph/Node.cpp generator/graph/Node.h generator/graph/Edge.cpp generator/graph/Edge.h generator/parser/GrammarParser.cpp generator/parser/GrammarParser.h generator/parser/ExpressionHandler.cpp generator/parser/ExpressionHandler.h generator/parser/ThompsonConstructor.cpp generator/parser/ThompsonConstructor.h generator/parser/utilities/string.cpp generator/parser/utilities/string.h generator/Pattern.cpp generator/Pattern.h)
add_executable(LexicalAnalyzer ${SOURCE_FILES})