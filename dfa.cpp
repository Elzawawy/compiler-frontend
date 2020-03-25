//
// Created by omar_swidan on 23/03/20.
//

#include "dfa.h"

// implement subset construction
DFAState DFA::GenerateDFA(NFAState &nfa_root_state, unordered_set<string> input_table) {
    vector<NFAState> nfa_start_states = EpsilonClosureOnNFAState(nfa_root_state);
    DFAState dfa_start_state = DFAState(false, nfa_start_states);

    unmarked_dfa_states_.insert(&dfa_start_state);

    while (!unmarked_dfa_states_.empty()) {
        DFAState *current_dfa_state = *unmarked_dfa_states_.begin();
        unmarked_dfa_states_.erase(unmarked_dfa_states_.begin());

        marked_dfa_states_.insert(current_dfa_state);

        for (const auto &input : input_table) {
            DFAState *new_dfa_state = EpsilonClosureOnNFAStates(Move(*current_dfa_state, input));
            if (marked_dfa_states_.find(new_dfa_state) == marked_dfa_states_.end()) {
                unmarked_dfa_states_.insert(new_dfa_state);
            }
            current_dfa_state->AddNeighbour(input, new_dfa_state);
        }
    }

    return DFAState(false, vector<NFAState>());
}

DFAState *DFA::EpsilonClosureOnNFAStates(vector<NFAState> nfa_states) {

    DFAState *dfa_state;
    return dfa_state;
}

vector<NFAState> DFA::Move(DFAState &dfa_state, string input) {
    return vector<NFAState>();
}

vector<NFAState> DFA::EpsilonClosureOnNFAState(NFAState &nfa_state) {
    return vector<NFAState>();
}
