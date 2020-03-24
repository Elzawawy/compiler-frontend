//
// Created by omar_swidan on 23/03/20.
//

#ifndef LEXGEN_DFA_H
#define LEXGEN_DFA_H

#include "dfa_state.h"
#include <unordered_set>
#include <string>

using namespace std;

class DFA {
private:
    DFAState EpsilonClosure(vector<NFAState> &nfa_states);

    vector<NFAState> Move(DFAState &dfa_state, string input);

    vector<NFAState> EpsilonClosure(NFAState &nfa_state);

public:
    DFAState GenerateDFA(NFAState &nfa_root_state, unordered_set<string> input_table);
};


#endif //LEXGEN_DFA_H
