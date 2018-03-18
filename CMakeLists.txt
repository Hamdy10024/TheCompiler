cmake_minimum_required(VERSION 3.8)
project(LexicalAnalyzer)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp generator/State.cpp generator/State.h generator/MinDFA.cpp generator/MinDFA.h generator/SymTable.h generator/SymTable.cpp)
add_executable(LexicalAnalyzer ${SOURCE_FILES})