//
// Created by omar_swidan on 23/03/20.
//

#include <stack>
#include "dfa.h"

// implement subset construction
DFAState DFA::GenerateDFA(NFAState &nfa_root_state, unordered_set<string> input_table) {
    unordered_set<NFAState *> nfa_start_states = EpsilonClosureOnNFAState(nfa_root_state);
    DFAState dfa_start_state = DFAState(false, nfa_start_states);

    unmarked_dfa_states_.insert(&dfa_start_state);

    while (!unmarked_dfa_states_.empty()) {
        DFAState *current_dfa_state = *unmarked_dfa_states_.begin();
        unmarked_dfa_states_.erase(unmarked_dfa_states_.begin());

        marked_dfa_states_.insert(current_dfa_state);

        for (const auto &input : input_table) {
            DFAState new_dfa_state = EpsilonClosureOnNFAStates(Move(*current_dfa_state, input));
            if (marked_dfa_states_.find(&new_dfa_state) == marked_dfa_states_.end()) {
                unmarked_dfa_states_.insert(&new_dfa_state);
            }
            current_dfa_state->AddNeighbour(input, &new_dfa_state);
        }
    }

    return DFAState(false, unordered_set<NFAState *>());
}

DFAState DFA::EpsilonClosureOnNFAStates(const vector<NFAState> &nfa_states) {
    DFAState dfa_state = DFAState(false, unordered_set<NFAState *>());

    if (nfa_states.empty()) {
        // create an dead state
    } else {
        unordered_set<NFAState *> dfa_state_generator;
        bool is_accepting_state = false;
        string token;
        for (auto nfa_state: nfa_states) {
            // check if the nfa state is accepting state to create an accepting dfa state with nfa state token
            dfa_state_generator.merge(EpsilonClosureOnNFAState(nfa_state));
        }

        if (is_accepting_state) {
            dfa_state = DFAAcceptanceState(true, unordered_set<NFAState *>(), token);
        } else {
            dfa_state = DFANormalState(false, unordered_set<NFAState *>());
        }
    }
    return dfa_state;
}

vector<NFAState> DFA::Move(const DFAState &dfa_state, const string &input) {
    vector<NFAState> nfa_states_neighbours;
    for (const auto &generator : dfa_state.get_generators()) {
        vector<pair<string, NFAState *>> generator_neighbours = generator->getNeighbours();
        for (const auto &generator_neighbour: generator_neighbours) {
            if (generator_neighbour.first == input) {
                nfa_states_neighbours.push_back(*generator_neighbour.second);
            }
        }
    }
    return nfa_states_neighbours;
}

unordered_set<NFAState *> DFA::EpsilonClosureOnNFAState(NFAState &nfa_state) {
    stack<NFAState> nfa_states_stack;
    unordered_set<NFAState *> nfa_states_neighbours;

    nfa_states_stack.push(nfa_state);
    nfa_states_neighbours.insert(&nfa_state);

    while (!nfa_states_stack.empty()) {
        NFAState current_nfa_state = nfa_states_stack.top();
        nfa_states_stack.pop();
        vector<pair<string, NFAState *>> current_nfa_state_neighbours = current_nfa_state.getNeighbours();
        for (const auto &current_nfa_state_neighbour: current_nfa_state_neighbours) {
            if (current_nfa_state_neighbour.first == "/L" and
                nfa_states_neighbours.find(current_nfa_state_neighbour.second) != nfa_states_neighbours.end()) {
                nfa_states_stack.push(*current_nfa_state_neighbour.second);
                nfa_states_neighbours.insert(current_nfa_state_neighbour.second);
            }
        }
    }
    return nfa_states_neighbours;
}
