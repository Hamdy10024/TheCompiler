/*
 * File:   DFA.h
 * Author: Dahlia
 *
 * Created on March 21, 2018, 12:49 AM
 */
#include "DFA.h"
#include "NFAState.h"
#include "dfa/DFAState.h"
#include <stack>
#include <string>
#include <queue>
#include <set>
#include <algorithm>
#include <utility>
#include "token_table.h"
#include <iostream>
using namespace std;
bool comparevec(vector<NFAState *> &a,vector<NFAState *> &b) {
    if(a.size()!=b.size())
        return  false;
    for(int i =0;i<a.size();i++)
    {
        bool t=false;
        for(int j=0;j<b.size();j++)
            t|=a[i]==b[j];
        if(!t)
            return  false;
    }
    return  true;
}
DFA::DFA(NFAState* startState,token_table * toktab)
{
    //cout <<"called constructor<"<<endl;
    this->startState = startState;
    counter = 0;
    this->tktab = toktab;
    //subsetConstruction();
    construct();
}
vector<vector<int> > DFA::getTransitionTable()
{
    return transitionTable;
}

vector<pair<int, int> > DFA::getStatesGroups()
{
    return statesGroups;
}

 void DFA::epsilonClosure(DFAState* Dstate)
{

    vector <NFAState*> list = Dstate -> getNFAStates();
    for (int i=0; i <list.size(); i++)
    {
        eclosure.push(list[i]);
    }
    while (eclosure.size())
    {
        NFAState* top =eclosure.top();
        eclosure.pop();
        epsilonStates2.clear();
        if (!foundEntry(top,epsilonStates2,Entry::lambda)) continue;
        for (int i=0; i<epsilonStates2.size(); i++)
        {
            if (!exists(epsilonStates2[i],Dstate))
            {
                NFAState* x = epsilonStates2[i];
                Dstate->addState(x);
                eclosure.push(x);
            }
        }
    }
}
///checks if DFA b subset contains NFA a
bool DFA::exists (NFAState* a, DFAState* b)
{
    for (int i=0; i< b->getNFAStates().size(); i++)
        if (a-> getID()== b-> getNFAStates()[i]-> getID())
            return true;
    return false;
}
///checks groups all entry s neighbours in the epsilonstates vector
bool DFA::foundEntry(NFAState* t,vector <NFAState*> &epsilonStates,Entry s)
{

    int index=t->getID();
    State::stateTransitions *trans =t->getETransitions();
    for (int i=0; i<trans->size(); i++)
    {
        if (trans->at(i).first == s)
        {
            epsilonStates.push_back((NFAState*)trans->at(i).second);
        }
    }
    return epsilonStates.size();
}

DFAState* DFA:: initiateDtransition()
{
    epsilonStates.clear();
    cout<<"init Dtrams"<<endl;
    DFAState* init = new DFAState(counter ++);
    init->addState(startState);
    cout<<"E closure"<<endl;
    if (foundEntry(startState,epsilonStates,Entry::lambda))
    {
        init->addStateSet(epsilonStates);
        epsilonClosure(init);
    }
    DFAstatesInc.push(init);

    DFAStates.push_back(init);

    setAcceptingState(init);
    statesGroups.push_back(make_pair(init->getID(), init->isAcceptingState()));


    cout<<"settings "<<(init == NULL) <<endl;
    int sz = init->all_entries().size();

    vector <int> vec(sz);

    transitionTable.push_back(vec);
    return init;

}
void DFA::setAcceptingState(DFAState* d)
{
    vector <NFAState*> states= d -> getNFAStates();
    vector <int> vec;
    for (int i=0; i<states.size(); i++)
    {
        if (states[i]->isAcceptingState())
            vec.push_back((int)states[i]->isAcceptingState());
    }
    if (vec.empty()) d->resetAccepting();
    else
    {
        sort (vec.begin(),vec.end());
        d->editAcceptingVal(vec[0]);
    }
}
bool comparator (NFAState* &a, NFAState* &b)
{
    return a->getID()< b->getID();
}
vector <NFAState*> DFA::move(DFAState* d, Entry ch)
{
     dstates=d->getNFAStates();
    //vector<NFAState*> sameEntryStates;
    st->clear();
    transitions.clear();
    st->clear();
    cout<<"bada2t move "<<dstates.size()<<" "<<ch.inp<<endl;
    for (int i = 0; i < dstates.size(); i++)
    {
        cout<<"adiiny ba move "<<dstates[i]->getID()<<endl;
        st = dstates[i]->getETransitions();
        for(int j = 0;j<st->size();j++) {
            if(st->at(j).first == ch) {
                    bool f = 0;
                for(int k = 0;k<transitions.size() && !f;k++) {
                    if(transitions[k] == (NFAState*)st->at(j).second)
                         f = 1;
                }
                if(!f)
                    transitions.push_back((NFAState*)st->at(j).second);
            }
        }
    }
    //sort(transitions.begin(),transitions.end(),comparator);
    return transitions;
}

vector<int> t1,t2;
bool DFA::checkSameStates(vector <NFAState*> v1, vector<NFAState*> v2)
{
    if (v1.size()!= v2.size())return false;
    for (int i = 0; i < v1.size(); i++)
    {
        t1.push_back(v1[i]->getID());
        t2.push_back(v2[i]->getID());
    }
    sort(t1.begin(), t1.end());
    sort(t2.begin(), t2.end());
    return(equal(t1.begin(), t1.end(), t2.begin()));
}
bool DFA::combine(DFAState* d)
{
    for (int i = 0; i < DFAStates.size(); i++)
    {
        vector <NFAState*> u=d->getNFAStates(),
                           v=DFAStates[i]->getNFAStates();
        if (checkSameStates(u,v))
        {
            d->setID(DFAStates[i]->getID());
            return true;
        }
    }
    return false;
}
map <NFAState*,bool> visi;
void DFA::DFS(NFAState * node,Entry inp , vector<NFAState*> &cals){
    if(visi.count(node))
        return;;
    visi[node] = 1;
    State::stateTransitions *ts = node->getETransitions();

    for(int i=0;i<ts->size();i++) {
        if(ts->at(i).first == inp) {
            DFS((NFAState*)ts->at(i).second,Entry::lambda,cals);
            cals.push_back((NFAState*)ts->at(i).second);
        }
    }
}
void DFA::construct() {
    counter = 0;
    epsilonStates.clear();
    DFAState *init = new DFAState(counter++);
    init->setID(0);
    visi.clear();
    DFS(startState,Entry::lambda,epsilonStates);
    init->addStateSet(epsilonStates);
    queue<DFAState*> alls;
    alls.push(init);
    map<DFAState*,bool>taken;

    while(!alls.empty()) {

        DFAState *curr = alls.front();
        alls.pop();
        if(curr->states.size() ==0 || taken.count(curr))
            continue;
        taken[curr] = 1;
        cout<<"having "<<curr->getID()<<endl;
        DFAStates.push_back(curr);
        all_en.clear();
        uniq.clear();
        all_en = curr->all_entries();
        for(int i = 0; i <all_en.size();i++) {
                if(uniq.count(all_en[i]))
                    continue;
                uniq.insert(all_en[i]);
            DFAState* u = new DFAState(counter++);
            u->setID(counter);
            epsilonStates.clear();
            visi.clear();
            for(int k = 0;k<curr->states.size();k++)
                DFS(curr->states[k],all_en[i],epsilonStates);
            u->addStateSet(epsilonStates);
            bool tr = false;
            for(int i=0;i<DFAStates.size();i++) {
                vector<NFAState*> now = u->getNFAStates();
                vector<NFAState*> now2=DFAStates[i]->getNFAStates();
                tr|=comparevec(now,now2);

                if(tr){

                    delete u;
                    u = DFAStates[i];
                    break;
                }
            }
            if(u->states.size()==0 )
            {

                delete u;
                continue;
            }
            curr->addTransition({all_en[i],u});
            alls.push(u);
        }
    }

    for (int i=0;i<DFAStates.size();i++) {
        trans[DFAStates[i]] = *DFAStates[i]->getETransitions();
        string this_token = "";
        for(int j=0;j< DFAStates[i]->states.size();j++)
        {
            Token nt = DFAStates[i]->states[j]->getToken();
            cout<<"Prefer "<<nt<<endl;
            if(tktab->compare_priority(nt,this_token) < 0) {

                DFAStates[i]->setAsAccepting(nt);
            this_token = nt;
            }
        }
    }


    MinDFA * minimizer= new MinDFA();
    transition_table = minimizer->minimize(trans,init);
    delete minimizer;

}

void DFA::subsetConstruction()
{

    cout <<"subset construction"<<endl;
    DFAState * init =   initiateDtransition();

    cout <<"grouping started "<<DFAstatesInc.size()<<endl;
    while (DFAstatesInc.size())
    {
        DFAState*d = DFAstatesInc.front();
        DFAstatesInc.pop();
        all_en= d->all_entries();
        cout<<"create neighbours "<<endl;
        for (int i=0; i<all_en.size(); i++)
        {
            cout<<"for entyr "<<all_en[i].inp<<endl;
            if(uniq.count(all_en[i]))
                continue;
            uniq.insert(all_en[i]);
            //char ch = token[i];
            x = move(d,all_en[i]);

            cout<<"still here "<<all_en.size()<<" "<<all_en[i].inp<<endl;
            DFAState* u =new DFAState(DFAStates.size());

            u->addStateSet(x);
            epsilonClosure(u);
            cout<<"yep sstill here "<<all_en.size()<<endl;
            if (u->getNFAStates().size() && !combine(u))
            {
                cout<<"then here "<<endl;
                u->setID(counter++);
                setAcceptingState(u);
                transitionTable.push_back(vector<int> (all_en.size()));
                DFAstatesInc.push(u);
                DFAStates.push_back(u);
                statesGroups.push_back(make_pair(u->getID(), u->isAcceptingState()));
                cout<<"moving out "<<u->getNFAStates().size()<<endl;
            }

            if (u->getNFAStates().size()){

                transitionTable[d->getID()][i] = u->getID();
                d->addTransition({all_en[i],u});
                cout<<"adding dfastaes "<<u->getNFAStates().size()<<endl;

            }
            else
                transitionTable[d->getID()][i] = -1;
        }
        cout<<"finished 1 cell "<<endl;

    }

    cout <<"Table constructor<"<<endl;

    for (int i=0;i<DFAStates.size();i++) {
        trans[DFAStates[i]] = *DFAStates[i]->getETransitions();
    }
    MinDFA * minimizer= new MinDFA();
    transition_table = minimizer->minimize(trans,init);

}
TransitionTable* DFA::getTable() {
return transition_table;
}

