#include "MinDFA.h"
#include "headers.h"
#include <set>
map <Token,Class> base_classes;
MinDFA::MinDFA()
{

}

void MinDFA::create_basis(TransitionTable::table &tab)
{
    map<State*,State::stateTransitions>::iterator it=tab.begin();
    for(it=tab.begin(); it!=tab.end(); it++)
    {
        states[it->first]=0;
        all_states.push_back(it->first);
        State::stateTransitions &st = it->second;
        for(int j=0; j<st.size(); j++)
        {
            if(!entr_row.count(st[j].first))
            {
                int t = entr_row.size();
                entr_row[st[j].first] = t;
            }
        }
        Token tok = ((DFAState *)it->first)->getToken();
        if(!token_row.count(tok))
        {
            int t = token_row.size();
            token_row[tok]=t;
            cout<< tok <<" ";
        }
    }
    cout<<endl;
    vector <Pattern> entr(entr_row.size());

    map<Pattern,int>::iterator i;
    for (i=entr_row.begin(); i!=entr_row.end(); i++)
    {
        entr[i->second] = i->first;
    }
    referenc = entr;

}
TransitionTable* MinDFA::minimize(TransitionTable::table &tab,State *start)
{

    create_basis(tab);
    map <vector<Class>,Class> classifier;
    map <State*,Class> identifier = states;
    int base_no = 1;
    int nbase;
    do
    {

        states = identifier;
        classifier.clear();
        for(int i=0; i<all_states.size(); i++)
        {
            State* curr = all_states[i];
            vector<Class> vals(referenc.size()+1,-1);
            for(int j=0; j<tab[curr].size(); j++)
            {
                Pattern entry = tab[curr][j].first;
                int ent_ind = entr_row[entry];
                vals[ent_ind] = states[tab[curr][j].second];

            }
            vals[vals.size()-1] = token_row[((DFAState*)curr)->getToken()];
            if(classifier.count(vals))
            {
                identifier[curr] = classifier[vals];
            }
            else
            {
                int t = classifier.size();
                classifier[vals] = t;
                identifier[curr] = t;
            }
        }
        nbase = base_no;
        base_no = classifier.size();

    }    while(base_no> nbase);
    return create_min_graph(base_no,start);

}


TransitionTable *MinDFA::create_min_graph(int b,State *start)
{
    vector<DFAState*> min_states;
    bool taken[b] ;

    for(int i=0; i <b; i++ )
    {
        taken[i] = 0;
        min_states.push_back(new DFAState(i));
        min_states[i]->setID(i);
    }
    for (int i = 0; i<all_states.size() && b; i++)
    {
        if(taken[states[all_states[i]]])
            continue;
        Class cl = states[all_states[i]];
        min_states[cl]->setAsAccepting(((DFAState*)all_states[i])->getToken());
        taken[cl] = true;
        b--;
        DFAState* mstate = min_states[cl];
        Token tk ="";
        for ( int j = 0; j < all_states[i]->getETransitions()->size() ; j++)
        {
            Pattern e = all_states[i]->getETransitions()->at(j).first;
            State* target =  all_states[i]->getETransitions()->at(j).second;
            Class tarcl = states[target];
            mstate->addTransition({e,min_states[tarcl]});
        }
    }
    TransitionTable::table tab;
    for(int i=0; i<min_states.size(); i++)
    {

        tab[min_states[i]] = *min_states[i]->getETransitions();
    }
    return (new TransitionTable(tab,min_states[states[start]]));
}

