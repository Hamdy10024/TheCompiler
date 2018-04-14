#include <sstream>
#include <iostream>
#include "generator/parser/GrammarParser.h"
#include "generator/nfa/NFA.h"
#include "new/DFA.h"
#include "new/Analyzer.h"

#include <map>
using  namespace std;

map<NFAState*,bool> visited;
void dfs(NFAState* curr) {
    if(visited.count(curr))
        return;
    visited[curr] = 1;
//    cout<<curr->getID()<<":-\t";
//    for(int i=0;i<curr->getETransitions()->size();i++){
//       // if(curr->getETransitions()->at(i).first ==Entry::lambda)continue;
//        cout<<curr->getETransitions()->at(i).first.st<<"-"<<curr->getETransitions()->at(i).first.en
//            <<":"<<curr->getETransitions()->at(i).second->getID()<<" ";
//    }
//
//
    // cout<<curr->getToken()<<endl;
    for(int i=0;i<curr->getETransitions()->size();i++){
        dfs((NFAState*)curr->getETransitions()->at(i).second);
    }
}
int main() {

    token_table *tokenTable = new token_table();
    ifstream myReadFile;
    myReadFile.open("test_2.txt");
    GrammarParser *parser = new GrammarParser("../grammar.txt", tokenTable);
    parser->parse();

    NFA *nfa = new NFA(parser->getRegExpressions(), parser->getKeywords(), parser->getPunctuations());
    nfa->combineNFA();
    NFAState *startState = nfa->getStartState();
    dfs(startState);

    SymTable *symtab = new SymTable();
    for (int i=0;i<tokenTable->token_tab.size();i++)
        symtab->insert_into_scanned_list(tokenTable->token_at(i));
    DFA *dfa = new DFA (startState,tokenTable);

    cout<<"chec2";
    TransitionTable *table;
    table = dfa->getTable();
    table->print();
    stringstream fortest;
    fortest <<"int while 098 xyz,x<2.3,float";
   // table->print();
    Analyzer * analyzer = new Analyzer(myReadFile,table,symtab);
    cout << "size = " << startState->getTransitions()->size() << "\n";

    for (auto trans : *startState->getTransitions()) {
        cout << trans.first->get() << "\t" << trans.second->isAcceptingState() << "\n";
    }
    ofstream myfile;
    myfile.open ("output.out");

    while(analyzer->has_next())
        myfile<<analyzer->next_token()<<endl;
    myfile.close();
    cout << "Hello, World!\n";
    return 0;
}