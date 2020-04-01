//
// Created by omar_swidan on 23/03/20.
//

#ifndef LEXGEN_DFA_H
#define LEXGEN_DFA_H

#include "dfa_state.h"
#include "utils.cpp"
#include <unordered_set>
#include <queue>
#include <string>

class DFA {
private:
    std::unordered_set<DFAState, DFAStateHashingFunction> marked_dfa_states_;

    std::queue<DFAState *> unmarked_dfa_states_queue_;
    std::unordered_set<DFAState, DFAStateHashingFunction> unmarked_dfa_states_set_;

    unordered_set<NFAState *> *EpsilonClosureOnNFAStates(const vector<NFAState> &nfa_states);

    vector<NFAState> *Move(const DFAState &dfa_state, const string &input);

    unordered_set<NFAState *> *EpsilonClosureOnNFAState(NFAState &nfa_state);

public:
    DFAState *GenerateDFA(NFAState &nfa_root_state, const unordered_set<string> &input_table);
};


#endif //LEXGEN_DFA_H
