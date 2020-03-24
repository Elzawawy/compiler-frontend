//
// Created by omar_swidan on 23/03/20.
//

#include "dfa.h"

// implement subset construction
DFAState DFA::GenerateDFA(NFAState &nfa_root_state, unordered_set<string> input_table) {
    return DFAState(false);
}

DFAState DFA::EpsilonClosure(vector<NFAState> &nfa_states) {
    return DFAState(false);
}

vector<NFAState> DFA::Move(DFAState &dfa_state, string input) {
    return vector<NFAState>();
}

vector<NFAState> DFA::EpsilonClosure(NFAState &nfa_state) {
    return vector<NFAState>();
}
