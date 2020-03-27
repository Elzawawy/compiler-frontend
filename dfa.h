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
    unordered_set<DFAState *> unmarked_dfa_states_, marked_dfa_states_;

    DFAState EpsilonClosureOnNFAStates(const vector<NFAState>& nfa_states);

    vector<NFAState> Move(const DFAState& dfa_state, const string& input);

    unordered_set<NFAState *> EpsilonClosureOnNFAState(NFAState &nfa_state);

public:
    DFAState GenerateDFA(NFAState &nfa_root_state, unordered_set<string> input_table);
};


#endif //LEXGEN_DFA_H
